#include "std/stralloc.h"

#include "std/mem.h"
#include <errno.h>
#include <stdlib.h>

int
stralloc_catb(struct stralloc *sa, const char *x, size_t n)
{
	if (!stralloc_ready(sa, sa->n + n)) return 0;
	mem_copy(sa->s + sa->n, x, n);
	sa->n += n;

	return 1;
}

void
stralloc_init(struct stralloc *sa)
{
	struct stralloc sa0 = STRALLOC_INIT;
	mem_copy(sa, &sa0, sizeof *sa);
}

void
stralloc_free(struct stralloc *sa)
{
	free(sa->s);
	stralloc_init(sa);
}

int
stralloc_ready(struct stralloc *sa, size_t n)
{
	size_t wanted = n + (n >> 3) + 30;
	char *x;

	if (sa->s && sa->a >= n) return 1;
	if (!(x = realloc(sa->s, wanted))) return 0;
	sa->a = wanted;
	sa->s = x;

	return 1;
}

void
stralloc_chomp(struct stralloc *sa)
{
	if (sa->n == 0) return;
	if (sa->s[sa->n - 1] == '\n') sa->n--;
	if (sa->n == 0) return;
	if (sa->s[sa->n - 1] == '\r') sa->n--;
}

void
stralloc_strip(struct stralloc *sa)
{
	for (; sa->n > 0; sa->n--) {
		char c = sa->s[sa->n - 1];
		if (c != ' ' && c != '\t') break;
	}
}