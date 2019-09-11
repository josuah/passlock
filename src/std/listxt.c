#include "std/listxt.h"

#include "std/buffer.h"
#include "std/fmt.h"
#include "std/open.h"
#include "std/str.h"
#include "std/stralloc.h"
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int
listxt_get(char *path, struct stralloc *sa, struct genalloc *ga, size_t n, char *s)
{
	char bx[1024];
	struct buffer b = BUFFER_INIT(read, 0, bx, sizeof bx);

	if ((b.fd = open_read(path)) == -1) return 0;

	while (listxt_getline(&b, sa, ga)) {
		if (genalloc_len(char *, ga) < n) continue;
		if (str_equal(genalloc_s(char *, ga)[n], s)) goto end;
	}
	genalloc_zero(char *, ga);
end:
	close(b.fd);
	return 1;
}

int
listxt_getline(struct buffer *b, struct stralloc *sa, struct genalloc *ga)
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
		if (!genalloc_cat(char *, ga, &s)) return 0;
		s[i] = 0;
		n -= i + 1;
		s += i + 1;
	}

	return 1;
}

int
listxt_put(struct buffer *b, struct genalloc *ga)
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
	return str_char(s, ':');
}

int
listxt_tmp(struct stralloc *sa, char const *path)
{
	char num[30];

	stralloc_zero(sa);
	if (!stralloc_cats(sa, path)) return 0;
	if (!stralloc_cats(sa, ".")) return 0;
	if (!stralloc_cats(sa, fmt(u64, num, getpid()))) return 0;
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