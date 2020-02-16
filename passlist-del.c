#include <stdio.h> /* for rename(2) */

#include "src/buffer.h"
#include "src/listxt.h"
#include "src/log.h"
#include "src/stralloc.h"

char *flag_f = "/etc/passlist/default";

void
usage(void)
{
	log_usage(arg_0, " [-v] [-f passfile] user");
}

int
main(int argc, char **argv)
{
	struct genalloc ga = GENALLOC_INIT;
	struct buffer bi = BUFFER_INIT(read, 0, bis, sizeof bis);
	struct buffer bo = BUFFER_INIT(write, 0, bos, sizeof bos);
	struct stralloc line = STRALLOC_INIT;
	struct stralloc tmp = STRALLOC_INIT;
	char *user, bis[1024], bos[1024];

	log_init(3);

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
		log_fatal(111, "invalid username");
	if (!listxt_get(flag_f, &line, &ga, 0, user))
		log_fatal(111, "open ", flag_f);
	if (genalloc_len(char *, &ga) == 0)
		log_fatal(111, "user ",user," absent from ",flag_f);

	if (!listxt_tmp(&tmp, flag_f))
		log_fatal(111, "alloc");
	if ((bi.fd = open(flag_f, O_RDONLY)) == -1)
		log_fatal(111, "open ",flag_f);
	if ((bo.fd = open(tmp.s, O_WRITE | O_TRUNC)) == -1)
		log_fatal(111, "open ",tmp.s);

	while (listxt_getline(&bi, &line, &ga)) {
		if (str_equal(genalloc_s(char *, &ga)[0], user))
			continue;
		if (!listxt_put(&bo, &ga))
			log_fatal(111, "write");
	}
	if (!buffer_flush(&bo))
		log_fatal(111, "write");

	if (rename(tmp.s, flag_f) == -1)
		log_fatal(111, tmp.s," -> ",flag_f);

	return 0;
}
