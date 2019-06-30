#include "stralloc.h"
#include "mem.h"

int
stralloc_catb(stralloc *sa, const char *x, size_t n)
{
	if (!stralloc_ready(sa, sa->n + n)) return 0;
	mem_copy(sa->s + sa->n, x, n);
	sa->n += n;
	return 1;
}
