#include <stdio.h> /* for rename(2) */

#include "src/buffer.h"
#include "src/listxt.h"
#include "src/log.h"
#include "src/stralloc.h"

char *flag_f = "/etc/passlist/default";
char *arg0 = NULL;

void
usage(void)
{
	fprintf(stderr, "usage: %s [-v] [-f passfile] user", arg0);
	exit(EX_USAGE);
}

int
main(int argc, char **argv)
{
	struct genalloc ga = GENALLOC_INIT;
	FILE *fi, *fo;
	struct stralloc line = STRALLOC_INIT;
	char path[2048];

	init(3);

	optind = 0;
	arg0 = *argv;
	while ((c = getopt(argc, argv, "vf:")) != -1) {
		switch (c) {
		case 'v':
			buffer_puts(buffer_1, VERSION);
			buffer_flush(buffer_1);
			break;
		case 'f':
			flag_f = optarg;
			break;
		case '?':
			usage();
		}
	}

	if (!(user = *argv++))
		usage();
	if (*argv)
		usage();

	if (!listxt_valid(user))
		fatal(111, "invalid username");
	if (!listxt_get(flag_f, &line, &ga, 0, user))
		fatal(111, "opening %s", flag_f);
	if (genalloc_len(char *, &ga) == 0)
		fatal(111, "user %s absent from %s", user, flag_f);

	if (!listxt_tmp(&tmp, flag_f))
		fatal(111, "alloc");
	if ((fi = fopen(flag_f, "r")) == -1)
		fatal(111, "open ",flag_f);
	if ((fo = fopen(path, "w")) == -1)
		fatal(111, "open ",tmp.s);

	while ((n = listxt_getline(fi, &ga)) > 0) {
		if (str_equal(genalloc_s(char *, &ga)[0], user))
			continue;
		if (listxt_put(fo, &ga) == -1)
			fatal(111, "write");
	}
	if (errno)
		fatal(111, "reding a line from %s", path);
	if (fflush(fo) == EOF)
		fatal(111, "write");

	if (rename(path, flag_f) == -1)
		fatal(111, "%s -> %s", path, flag_f);

	return 0;
}
