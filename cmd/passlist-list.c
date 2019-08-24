#include "std/arg.h"
#include "std/buffer.h"
#include "std/genalloc.h"
#include "std/listxt.h"
#include "std/log.h"
#include "std/open.h"
#include "std/stralloc.h"

char *flag_f = "/etc/passlist/default";

void
usage(void)
{
	log_usage(arg_0, " [-v] [-f passfile]");
}

int
main(int argc, char **argv)
{
	char bs[1024];
	struct buffer b = BUFFER_INIT(read, 0, bs, sizeof bs);
	struct stralloc sa = STRALLOC_INIT;
	struct genalloc ga = GENALLOC_INIT;

	log_init();

	ARG_BEGIN {
	case 'v':
		buffer_puts(buffer_1, VERSION);
		buffer_flush(buffer_1);
		return 0;
	case 'f':
		flag_f = ARG;
		break;
	default:
		usage();
	} ARG_END;

	if (*argv) usage();

	if ((b.fd = open_read(flag_f)) == -1) log_fatal_sys(111, "open ",flag_f);

	buffer_puts(buffer_1, "user                      path\n");
	while (listxt_getline(&b, &sa, &ga)) {
		buffer_puts(buffer_1, " ");
		buffer_puts(buffer_1, genalloc_s(char *, &ga)[0]);
		buffer_pad(buffer_1, genalloc_s(char *, &ga)[0], " ", 95);
		buffer_puts(buffer_1, " ");
		buffer_puts(buffer_1, genalloc_s(char *, &ga)[2]);
		buffer_puts(buffer_1, "\n");
	}

	if (!buffer_flush(buffer_1)) log_fatal_sys(111, "write");

	return 0;
}
