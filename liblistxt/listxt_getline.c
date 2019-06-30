#include "listxt.h"

int
listxt_getline(buffer *b, stralloc *sa, genalloc *ga)
{
	size_t i;
	size_t n;
	int r;
	char *s;

	if (!buffer_getline(b, sa)) return 0;
	stralloc_chomp(sa);

	s = sa->s;
	n = sa->n;
	do {
		if (!genalloc_catx(char *, ga, s)) return 0;
		if (s[i] == '\n' || s[i] == ':') s[i] = 0;
		n -= i + 1;
		s += i + 1;
	} while ((i = listxt_scan(s)) < n);

	return 0;
}
