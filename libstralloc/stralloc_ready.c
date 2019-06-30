#include "stralloc.h"
#include <errno.h>
#include <stdlib.h>

int
stralloc_ready(stralloc *sa, size_t n)
{
	size_t wanted = n + (n >> 3) + 30;
	char *x;
	
	if (sa->s && sa->a >= n) return 1;
	if (!sa->h) return errno = EMSGSIZE, 0;
	if (!(x = realloc(sa->s, wanted))) return 0;
	sa->a = wanted;
	sa->s = x;
	return 1;
}
