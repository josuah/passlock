#include <errno.h>
#include <stdlib.h>
#include "mem.h"
#include "stralloc.h"

int
stralloc_catb(stralloc *sa, const char *x, size_t n)
{
	if (!stralloc_ready(sa, sa->n + n)) return 0;
	mem_copy(sa->s + sa->n, x, n);
	sa->n += n;
	return 1;
}

int
stralloc_catc(stralloc *sa, char c)
{
	return stralloc_catb(sa, &c, 1);
}

void
stralloc_chomp(stralloc *sa)
{
	if (sa->n == 0) return;
	if (sa->s[sa->n - 1] == '\n') sa->n--;
	if (sa->n == 0) return;
	if (sa->s[sa->n - 1] == '\r') sa->n--;
}

void
stralloc_free(stralloc *sa)
{
	free(sa->s);
	sa->s = 0;
	sa->a = 0;
	sa->n = 0;
}

int
stralloc_ready(stralloc *sa, size_t n)
{
	size_t wanted = n + (n >> 3) + 30;
	char *x;

	if (sa->s && sa->a >= n) return 1;
	if (!(x = realloc(sa->s, wanted))) return 0;
	sa->a = wanted;
	sa->s = x;
	return 1;
}
