#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "listxt.h"
#include "log.h"

char *file = "/etc/passlist/default";
char *arg0 = NULL;

void
usage(void)
{
	fprintf(stderr, "usage: %s [-v] [-f passfile]\n", arg0);
	exit(100);
}

int
main(int argc, char **argv)
{
	FILE *fp;
	char *line, *user, *path;
	size_t sz;
	ssize_t un, pn;
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

	if (*argv)
		usage();

	fp = fopen(file, "r");
	if (fp == NULL) {
		warn("open, open!");
		die(111, "opening %s", file);
	}

	sz = 0;
	line = NULL;
	while (listxt_getline(&line, &sz, fp) > -1) {
		assert((un = listxt_field(line, 0, &user)) <= INT_MAX);
		assert((pn = listxt_field(line, 2, &path)) <= INT_MAX);
		assert(un > -1);
		listxt_fmt(&path, &pn);
		fprintf(stdout, " %-22.*s %.*s\n", (int)un, user, (int)pn, path);
	}
	if (ferror(fp))
		die(111, "getting a line from %s", file);
	free(line);
	return 0;
}
