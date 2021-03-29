#include "util.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *arg0;

static void
log_vprintf(char const *flag, char const *fmt, va_list va)
{
	int old_errno = errno;

	if (arg0 != NULL)
		fprintf(stderr, "%s: ", arg0);

	fprintf(stderr, "%s: ", flag);
	vfprintf(stderr, fmt, va);

	if (old_errno != 0)
		fprintf(stderr, ": %s", strerror(old_errno));

	fprintf(stderr, "\n");
	fflush(stderr);
}

void
die(char const *fmt, ...)
{
	va_list va;

	va_start(va, fmt); log_vprintf("error", fmt, va); va_end(va);
	exit(1);
}

void
warn(char const *fmt, ...)
{
	va_list va;

	va_start(va, fmt); log_vprintf("warn", fmt, va); va_end(va);
}

void
debug(char const *fmt, ...)
{
	va_list va;
	static char *log_debug = NULL;

	if (!log_debug)
		log_debug = getenv("DEBUG");
	if (!log_debug)
		return;
	va_start(va, fmt); log_vprintf("debug", fmt, va); va_end(va);
}

/*
 * Remove one newline character from the end of the string if any
 * and return 1, or 0 if there is not one.
 */
int
strchomp(char *s)
{
	size_t len;

	len = strlen(s);
	if (len > 0 && s[len - 1] == '\n') {
		s[len - 1] = '\0';
		return 1;
	}
	return 0;
}

size_t
strlcpy(char *buf, char const *str, size_t sz)
{
	size_t len, cpy;

	len = strlen(str);
	cpy = (len > sz) ? (sz) : (len);
	memcpy(buf, str, cpy + 1);
	buf[sz - 1] = '\0';
	return len;
}
