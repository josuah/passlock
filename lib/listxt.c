#include "listxt.h"

#include "buffer.h"
#include "fd.h"
#include "fmt.h"
#include "open.h"
#include "str.h"
#include "stralloc.h"
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int
listxt_get(char *path, stralloc *sa, genalloc *ga, size_t n, char *s)
{
	char bx[1024];
	buffer b = BUFFER_INIT(read, 0, bx, sizeof bx);

	if ((b.fd = open_read(path)) == -1) return 0;

	while (listxt_getline(&b, sa, ga)) {
		if (genalloc_len(char *, ga) < n) continue;
		if (str_equal(genalloc_s(char *, ga)[n], s)) goto end;
	}
	genalloc_zero(char *, ga);
end:
	fd_close(b.fd);
	return 1;
}

int
listxt_getline(buffer *b, stralloc *sa, genalloc *ga)
{
	size_t i, n;
	char *s;

	if (!buffer_getline(b, sa)) return 0;
	stralloc_chomp(sa);
	if (!stralloc_cat0(sa)) return 0;

	s = sa->s;
	n = sa->n;
	genalloc_zero(char *, ga);
	while ((i = listxt_scan(s)) < n) {
		if (!genalloc_catx(char *, ga, &s)) return 0;
		s[i] = 0;
		n -= i + 1;
		s += i + 1;
	}

	return 1;
}

int
listxt_put(buffer *b, genalloc *ga)
{
	size_t i;

	for (i = 0; i < genalloc_len(char *, ga); i++) {
		if (i > 0) if (!buffer_puts(b, ":")) return 0;
		if (!buffer_puts(b, genalloc_s(char *, ga)[i])) return 0;
	}
	if (!buffer_puts(b, "\n")) return 0;
	return 1;
}

size_t
listxt_scan(char *s)
{
	return str_chr(s, ':');
}

int
listxt_tmp(stralloc *sa, char const *path)
{
	char num[50];

	num[fmt_long(num, getpid())] = '\0';
	stralloc_zero(sa);
	if (!stralloc_cats(sa, path)) return 0;
	if (!stralloc_cats(sa, ".")) return 0;
	if (!stralloc_cats(sa, num)) return 0;
	if (!stralloc_cat0(sa)) return 0;

	return 1;
}

int
listxt_valid(char *s)
{
	while (1) switch (*s++) {
	case '\0': return 1;
	case '\n': case '\r': case ':': return 0;
	}
}
