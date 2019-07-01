#include "arg.h"
#include "buffer.h"
#include "die.h"
#include "genalloc.h"
#include "listxt.h"
#include "log.h"
#include "open.h"
#include "stralloc.h"

char *flag_f = NULL;

void
usage(void)
{
	log_usage(arg_0, "-f passfile");
}

int
main(int argc, char **argv)
{
	log_init();
	char bs[1024];
	char *gs[3];
	buffer b = BUFFER_INIT(read, 0, bs, sizeof bs);
	stralloc sa = STRALLOC_INIT(0);
	genalloc ga = GENALLOC_INIT(gs);

	ARG_BEGIN {
	case 'f': flag_f = ARG; break;
	default: usage();
	} ARG_END;

	if (!flag_f) usage();
	if (*argv) usage();

	if ((b.fd = open_read(flag_f)) == -1) die_open(flag_f);

	buffer_puts(buffer_1, "user            path\n");
	while (listxt_getline(&b, &sa, &ga)) {
		buffer_puts(buffer_1, " ");
		buffer_puts(buffer_1, genalloc_s(char *, &ga)[0]);
		buffer_pad(buffer_1, genalloc_s(char *, &ga)[0], 15, ' ');
		buffer_puts(buffer_1, " ");
		buffer_puts(buffer_1, genalloc_s(char *, &ga)[2]);
		buffer_puts(buffer_1, "\n");
	}

	if (!buffer_flush(buffer_1)) die_write();

	return 0;
}
