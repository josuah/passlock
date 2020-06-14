#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sodium.h>

#include "util.h"
#include "log.h"

char *arg0 = NULL;
char *flag['z'] = {0};

void
usage(void)
{
	fprintf(stdout, "usage: %s"
	  " [-v] -p /path/%%/pass user <passphrase\n", arg0);
	exit(1);
}

int
main(int argc, char **argv)
{
	char *user, *pass, path_tmp[2048], path_dst[2048];
	char hash[crypto_pwhash_STRBYTES];
	int fd, c, e;
	size_t sz;
	ssize_t w;

	optind = 0;
	arg0 = *argv;
	while ((c = getopt(argc, argv, "vp:")) != -1) {
		if (c == '?')
			usage();
		flag[c] = optarg ? optarg : "1";
	}
	argv += optind;
	argc -= optind;

	if (flag['v'])
		fprintf(stdout, "%s\n", VERSION), exit(0);
	if (flag['p'] == NULL)
		usage();
	if ((user = *argv++) == NULL || !is_valid(user))
		warn("invalid username"), usage();
	if (*argv != NULL)
		usage();

	sz = sizeof(path_dst);
	if (path_fmt(path_dst, sz, flag['p'], user) < 0)
		errno=ENAMETOOLONG, die("building destination path");

	sz = sizeof(path_tmp);
	if (snprintf(path_tmp, sz, "%s.%d", path_dst, getpid()) >= (int)sz)
		errno=ENAMETOOLONG, die("building temporary path");

	if ((fd = open(path_tmp, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		die("opening %s", path_tmp);

	e = errno;
	if (isatty(0)) {
		fprintf(stdout, "enter passphrase: ");
		fflush(stdout);
	}
	errno = e;

	sz = 0;
	pass = NULL;
	if (getline(&pass, &sz, stdin) < 0)
		die("reading stdin");
	strchomp(pass);

	info("hashing password");
	if (crypto_pwhash_str(hash, pass, strlen(pass),
	  crypto_pwhash_OPSLIMIT_INTERACTIVE,
	  crypto_pwhash_MEMLIMIT_INTERACTIVE) < 0)
		die("hashing password");

	free(pass);

	w = strlen(hash);
	if (write(fd, hash, w) < w || write(fd, "\n", 1) < 1)
		die("writing to file");
	close(fd);

	if (rename(path_tmp, path_dst) < 0)
		die("renaming from '%s' to '%s'", path_tmp, path_dst);

	return 0;
}
