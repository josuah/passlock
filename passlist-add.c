#include <stdio.h>  /* for rename(2) */
#include <fcntl.h>
#include <unistd.h>

#include <sodium.h>

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
	FILE *frd, *fwr;
	struct listxt *lst;
	ssize_t n;
	int c;

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
	if (user == NULL || !listxt_valid(user)) {
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

	n = listxt_get(file, &line, 0, user);
	if (n == -1)
		fatal(111, "getting value from %s", file);
	if (n > 0)
		fatal(1, "user %s exist on %s", user, file);

	frd = fopen(file, "r");
	if (frd == NULL)
		fatal(111, "opening %s", file);

	if (listxt_tmp(tmp, sizeof(tmp), file) == -1)
		fatal(111, "alloc");

	fwr = fopen(file, "w");
	if (fwr == NULL)
		fatal(111, "opening %s", tmp);

	fdump(frd, fwr);
	if (ferror(frd) || ferror(fwr))
		fatal(111, "copying from %s to %s", file, tmp);

	fclose(frd);

	pass = NULL;
	if (getline(&pass, &n, stdin) == -1)
		fatal(111, "reading stdin");
	strchomp(pass);

	debug("hashing password");
	assert(crypto_pwhash_str(hash, pass, n,
		crypto_pwhash_OPSLIMIT_MODERATE,
		crypto_pwhash_MEMLIMIT_MODERATE) == 0);

	free(pass);

	fprintf(fwr, "%s:%s:%s\n", user, hash, tmp);
	fflush(fwr);
	if (ferror(fwr))
		fatal(111, "writing to file");

	if (rename(tmp, file) == -1)
		fatal(111, "renaming from '%s' to '%s'", tmp, file);

	return 0;
}
