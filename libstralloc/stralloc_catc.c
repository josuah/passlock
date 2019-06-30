#include "stralloc.h"

int
stralloc_catc(stralloc *sa, char c)
{
	return stralloc_catb(sa, &c, 1);
}
