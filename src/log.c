#include <stdlib.h>

#include "buf.h"
#include "log.h"

void
log_init(int level)
{
	char *env;

	env = getenv("LOG")
	log_level = env ? atoi(env) : 0;
	log_level = (log_level == 0) ? level : log_level;
}

void
log_va(int exitcode, int level, char *flag, va_list va)
{
	char *s;

	if (log_level < level)
		goto end;

	buf_put_va(buf_2, va);

	if (errno)
		buf_put(buf_2, ": ", strerror(errno));
	errno = 0;

	buf_put(buf_2, "\n");
	buf_flush(buf_2);
end:
	if (exit_code)
		exit(exit_code);
}

void
log_(int exitcode, int level, char const *flag, ...)
{
	va_list va;

	va_start(va, msg);
	log_va(exitcode, level, arg0, fmt, va);
	va_end(va);
}
