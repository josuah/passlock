#include "util.h"

#include <string.h>
#include <ctype.h>
#include <errno.h>

size_t
strlcpy(char *buf, const char *str, size_t sz)
{
	size_t len, cpy;

	cpy = ((len = strlen(str)) > sz) ? (sz) : (len);
	memcpy(buf, str, cpy + 1);
	buf[sz - 1] = '\0';
	return len;
}

/*
 * Remove one newline character from the end of the string if any
 * and return 1, or 0 if there is not one.
 */
int
strchomp(char *s)
{
	size_t n;

	n = strlen(s);
	if (n > 0 && s[n - 1] == '\n') {
		s[n - 1] = '\0';
		return 1;
	}
	return 0;
}

int
is_valid(char *s)
{
	if (strcmp(s, ".") == 0 || strcmp(s, "..") == 0)
		return 0;
        for (; *s != '\0'; s++)
                if ((!isalnum(*s) && !ispunct(*s)) || *s == '/')
			return 0;
        return 1;
}

int
path_fmt(char *buf, size_t len, char *fmt, char *name)
{
	if (!is_valid(name))
		return errno=EINVAL, -1;
	for (; *fmt != '\0'; fmt++) {
		if (*fmt == '%') {
			size_t i;

			if ((i = strlcpy(buf, name, len)) >= len)
				return errno=ENAMETOOLONG, -1;
			buf += i;
			len -= i;
		} else {
			if (--len == 0)
				return errno=ENAMETOOLONG, -1;
			*buf++ = *fmt;
		}
	}
	if (--len == 0)
		return errno=ENAMETOOLONG, -1;
	*buf++ = '\0';
	return 0;
}
