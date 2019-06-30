#include "log.h"

#include "buffer.h"
#include <stdlib.h>

void
log_usage(char const *prog, char const *usage)
{
	buffer_puts(buffer_2, "usage: ");
	buffer_puts(buffer_2, prog);
	buffer_puts(buffer_2, " ");
	buffer_puts(buffer_2, usage);
	buffer_puts(buffer_2, "\n");
	buffer_flush(buffer_2);

	exit(1);
}
