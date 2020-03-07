#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "listxt.h"
#include "log.h"

char *file = "/etc/passlist/default";
char *arg0 = NULL;

void
usage(void)
{
	fprintf(stderr, "usage: %s [-v] [-f passfile] user\n", arg0);
	exit(100);
}

int
main(int argc, char **argv)
{
	FILE *frd, *fwr;
	char tmp[2048], *user, *line;
	size_t sz;
	ssize_t r;
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
	argc -= optind;
	argv += optind;

	if ((user = *argv++) == NULL)
		usage();
	if (*argv)
		usage();

	if (!listxt_isvalid(user))
		die(111, "invalid username");

	if ((line = listxt_get(file, 0, user)) == NULL) {
		if (errno)
			die(111, "opening %s", file);
		die(100, "user %s not in %s", user, file);
	}

	if (listxt_tmppath(tmp, sizeof tmp, file) == -1)
		die(111, "building temporary path");
	if ((frd = fopen(file, "r")) == NULL)
		die(111, "opening ",file);
	if ((fwr = fopen(tmp, "w")) == NULL)
		die(111, "opening %s", tmp);

	sz = 0;
	while ((r = listxt_getline(&line, &sz, frd)) > -1) {
		if (listxt_cmp(line, 0, user) == 0)
			continue;
		if (fprintf(fwr, "%s\n", line) < 0)
			die(111, "write");
	}
	fflush(fwr);
	if (errno)
		die(111, "reding from %s and writing to %s", file, tmp);

	if (rename(tmp, file) == -1)
		die(111, "%s -> %s", tmp, file);

	return 0;
}
