#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "listxt.h"
#include "log.h"

char *file = "/etc/passlist/default";
char *arg0 = NULL;

void
usage(void)
{
	fprintf(stderr, "usage: %s [-v [-f passfile]\n", arg0);
	exit(100);
}

int
main(int argc, char **argv)
{
	FILE *fp;
	char *list[3];
	size_t sz;
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

	if (*argv)
		usage();

	fp = fopen(file, "r");
	if (fp == NULL)
		fatal(111, "opening ",file);

	sz = 0;
	while (listxt_getline(&line, &sz, fp) > 0) {
		fprintf(stdout, " %-22s %s\n", list[0], list[2]);
	}
	free(list[0]);

	return 0;
}
