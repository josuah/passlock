#include "log.h"

#include "buffer.h"
#include <stdarg.h>
#include <stdlib.h>

void
log_die(int e, char const *type, int argc, ...)
{
	va_list a;

	va_start(a, argc);
	buffer_puts(buffer_2, type);
	buffer_puts(buffer_2, ": ");
	for (int x = 0; x < argc; x++) {
		char *s = va_arg(a, char *);
		buffer_puts(buffer_2, s);
	}
	buffer_puts(buffer_2, "\n");
	buffer_flush(buffer_2);
	va_end(a);

	exit(e);
}
