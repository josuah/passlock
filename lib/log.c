#include "log.h"
#include <stdarg.h>
#include "int.h"
#include <errno.h>
#include "str.h"
#include <stdlib.h>
#include "env.h"
#include "buffer.h"

int log_level = 3;

void
log_init(void)
{
	char *s;
	u32 u;

	if (!(s = env_get("LOG_LEVEL"))) return;
	if (s[u32_scan_base(&u, s, strlen(s), 10)] != '\0') return;
	log_level = u;
}

void
log_put(int level, int e, int sys, ...)
{
	va_list a;

	if (level > log_level) return;
	va_start(a, sys);
	for (char *s; (s = va_arg(a, char *)); buffer_puts(buffer_2, s));
	if (sys) {
		buffer_puts(buffer_2, ": ");
		buffer_puts(buffer_2, strerror(errno));
	}
	buffer_puts(buffer_2, "\n");
	buffer_flush(buffer_2);
	va_end(a);

	if (e > 0) exit(e);
}
