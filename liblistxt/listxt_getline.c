#include "listxt.h"
#include "str.h"

int
listxt_getline(buffer *b, stralloc *sa, genalloc *ga)
{
	size_t i = 0;
	size_t n = 0;
	char *s;

	genalloc_zero(char *, ga);
	if (!buffer_getline(b, sa)) return 0;
	stralloc_chomp(sa);
	if (!stralloc_cat0(sa)) return 0;

	s = sa->s;
	n = sa->n;
	while ((i = listxt_scan(s)) < n) {
		if (!genalloc_catx(char *, ga, s)) return 0;
		s[i] = 0;
		n -= i + 1;
		s += i + 1;
	}

	return 1;
}
