#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "def.h"

/*
 * An strsep() that does not skip consecutive occurence of the delimiter.
 */
char *
strfield(char **strp, const char *sep)
{
	char	*s, *prev;

	if (*strp == NULL)
		return NULL;
	for (s = prev = *strp; strchr(sep, *s) == NULL; s++)
		continue;
	if (*s == '\0') {
		*strp = NULL;
		return prev;
	}
	*s = '\0';
	*strp = s + 1;

	return prev;
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

void
strsplit(char **list, size_t n, char *s, char *sep)
{
	while (n--)
		*list++ = strfield(&s, *sep);
}

void
memtr(char *buf, size_t sz, char c1, char c2)
{
	char *cp;

	cp = buf;
	while ((cp = memchr(cp, sz + buf - cp, c1)))
		*cp = c2;
}

int
fdump(int frd, int fwr)
{
	char buf[8192];
	ssize_t r;

	while ((r = read(frd, buf, sizeof buf)) > 0)
		if (write(fwr, buf, r) < r)
			return -1;
	return r > 0 ? 0 : -1;
}
