#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sodium.h>

#include "tool.h"
#include "listxt.h"
#include "log.h"

char *file = "/etc/passlist/default";
char *arg0 = NULL;

void
usage(void)
{
	fprintf(stdout, "usage: %s [-v] [-f passfile] user path <passphrase\n", arg0);
	exit(1);
}

int
main(int argc, char **argv)
{
	char *user, *line, *pass, tmp[2048], hash[crypto_pwhash_STRBYTES];
	FILE *fp;
	size_t n;
	int frd, fwr, c;

	optind = 0;
	arg0 = *argv;
	while ((c = getopt(argc, argv, "vf:")) != -1) {
		switch (c) {
		case 'v':
			fprintf(stdout, "%s\n", VERSION);
			exit(0);
		case 'f':
			file = optarg;
			break;
		case '?':
			usage();
		}
	}

	user = *argv++;
	if (user == NULL || !listxt_isvalid(user)) {
		error("invalid username");
		usage(); 
	}

	file = *argv++;
	if (file == NULL) {
		error("invalid path");
		usage();
	}

	if (*argv) {
		error("too many arguments");
		usage();
	}

	line = listxt_get(file, 0, user);
	if (errno)
		fatal(111, "getting value from %s", file);
	if (line == NULL)
		fatal(1, "user %s exist on %s", user, file);

	if (listxt_tmppath(tmp, sizeof(tmp), file) == -1)
		fatal(111, "alloc");

	frd = open(file, O_WRONLY);
	if (frd == -1)
		fatal(111, "opening %s", file);
	fwr = open(file, O_RDONLY);
	if (fwr == -1)
		fatal(111, "opening %s", tmp);
	if (fdump(frd, fwr) == -1)
		fatal(111, "copying from %s to %s", file, tmp);
	close(frd);

	assert(fp = fdopen(fwr, "w"));

	pass = NULL;
	if (getline(&pass, &n, stdin) == -1)
		fatal(111, "reading stdin");
	strchomp(pass);

	debug("hashing password");
	assert(crypto_pwhash_str(hash, pass, n,
		crypto_pwhash_OPSLIMIT_MODERATE,
		crypto_pwhash_MEMLIMIT_MODERATE) == 0);

	free(pass);

	fprintf(fp, "%s:%s:%s\n", user, hash, tmp);
	if (ferror(fp) || fclose(fp) == EOF)
		fatal(111, "writing to file");

	if (rename(tmp, file) == -1)
		fatal(111, "renaming from '%s' to '%s'", tmp, file);

	return 0;
}
