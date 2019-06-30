#include "stralloc.h"

void
stralloc_chomp(stralloc *sa)
{
	if (sa->n == 0) return;
	if (sa->s[sa->n - 1] == '\n') sa->n--;
	if (sa->n == 0) return;
	if (sa->s[sa->n - 1] == '\r') sa->n--;
}
