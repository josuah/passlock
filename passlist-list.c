#include "src/arg.h"
#include "src/buffer.h"
#include "src/genalloc.h"
#include "src/listxt.h"
#include "src/log.h"
#include "src/open.h"
#include "src/stralloc.h"

char *flag_f = "/etc/passlist/default";

void
usage(void)
{
	log_usage(arg_0, " [-v] [-f passfile]");
}

int
main(int argc, char **argv)
{
	struct buffer b = BUFFER_INIT(read, 0, bs, sizeof bs);
	struct stralloc sa = STRALLOC_INIT;
	struct genalloc ga = GENALLOC_INIT;
	char bs[1024];

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

	if (*argv)
		usage();

	if ((b.fd = open(flag_f, O_RDONLY)) == -1)
		log_fatal(111, "open ",flag_f);

	buffer_puts(buffer_1, "user                      path\n");
	while (listxt_getline(&b, &sa, &ga)) {
		buffer_puts(buffer_1, " ");
		buffer_puts(buffer_1, genalloc_s(char *, &ga)[0]);
		buffer_pad(buffer_1, genalloc_s(char *, &ga)[0], ' ', 95);
		buffer_puts(buffer_1, " ");
		buffer_puts(buffer_1, genalloc_s(char *, &ga)[2]);
		buffer_puts(buffer_1, "\n");
	}

	if (!buffer_flush(buffer_1)) log_fatal(111, "write");

	return 0;
}
