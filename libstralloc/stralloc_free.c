#include "stralloc.h"
#include <stdlib.h>

void
stralloc_free(stralloc *sa)
{
	free(sa->s);
	sa->s = 0;
	sa->a = 0;
	sa->n = 0;
}
