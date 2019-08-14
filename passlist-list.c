#include "arg.h"
#include "buffer.h"
#include "genalloc.h"
#include "listxt.h"
#include "log.h"
#include "open.h"
#include "stralloc.h"

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
	buffer b = BUFFER_INIT(read, 0, bs, sizeof bs);
	stralloc sa = STRALLOC_INIT;
	genalloc ga = GENALLOC_INIT;

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

	if ((b.fd = open_read(flag_f)) == -1) log_fatalsys("open ",flag_f);

	buffer_puts(buffer_1, "user                      path\n");
	while (listxt_getline(&b, &sa, &ga)) {
		buffer_puts(buffer_1, " ");
		buffer_puts(buffer_1, genalloc_s(char *, &ga)[0]);
		buffer_pad(buffer_1, genalloc_s(char *, &ga)[0], 25, ' ');
		buffer_puts(buffer_1, " ");
		buffer_puts(buffer_1, genalloc_s(char *, &ga)[2]);
		buffer_puts(buffer_1, "\n");
	}

	if (!buffer_flush(buffer_1)) log_fatalsys("write");

	return 0;
}
