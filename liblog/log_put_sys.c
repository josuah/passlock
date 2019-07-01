#include "log.h"
#include "buffer.h"
#include <errno.h>
#include <stdarg.h>

void
log_put_sys(int level, char const *type, int argc, ...)
{
	va_list a;

	if (level > log_level) return;
	va_start(a, argc);
	buffer_puts(buffer_2, type);
	buffer_puts(buffer_2, ": ");
	for (int x = 0; x < argc; x++) {
		char *s = va_arg(a, char *);
		buffer_puts(buffer_2, s);
	}
	buffer_puts(buffer_2, ": ");
	buffer_puts(buffer_2, strerror(errno));
	buffer_puts(buffer_2, "\n");
	buffer_flush(buffer_2);
	va_end(a);
}
