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
	  " [-v] -p /path/%%/pass/ user <passphrase\n", arg0);
	exit(1);
}

int
main(int argc, char **argv)
{
	char *user, *pass, tmp[2048], dst[2048];
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

	if (path_fmt(dst, sizeof(dst), flag['p'], user) < 0)
		die("building password file path '%s'", flag['p']);
	sz = sizeof(tmp);
	if (snprintf(tmp, sz, "%s.%d", dst, getpid()) >= (int)sz)
		die("building temporary path");

	if ((fd = open(tmp, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		die("opening %s", tmp);

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
	  crypto_pwhash_OPSLIMIT_MODERATE,
	  crypto_pwhash_MEMLIMIT_MODERATE) < 0)
		die("hashing password");

	free(pass);

	w = strlen(hash);
	if (write(fd, hash, w) < w || write(fd, "\n", 1) < 1)
		die("writing to file");
	close(fd);

	if (rename(tmp, dst) < 0)
		die("renaming from '%s' to '%s'", tmp, dst);

	return 0;
}
