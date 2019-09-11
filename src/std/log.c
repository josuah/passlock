#include "std/buffer.h"
#include "std/env.h"
#include "std/int.h"
#include "std/log.h"
#include "std/str.h"
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>

int log_level = 9;

void
log_init(int level)
{
	char *s;
	u32 u;

	log_level = level;

	if (!(s = env_get("LOG_LEVEL"))) return;
	if (s[u32_scan_base(s, &u, 10)] != '\0') return;
	log_level = u;
}

void
log_put(int level, int e, char const *file, u64 line, ...)
{
	va_list a;

	if (level > log_level) return;
	va_start(a, line);
	for (char *s; (s = va_arg(a, char *)); buffer_puts(buffer_2, s));
	if (errno) {
		buffer_puts(buffer_2, ": ");
		buffer_puts(buffer_2, strerror(errno));
		buffer_puts(buffer_2, " {");
		buffer_puts(buffer_2, file);
		buffer_puts(buffer_2, ":");
		buffer_putn(buffer_2, line);
		buffer_puts(buffer_2, "}");
	}
	buffer_puts(buffer_2, "\n");
	buffer_flush(buffer_2);
	va_end(a);

	if (e > 0) exit(e);
}
