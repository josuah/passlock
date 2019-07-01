#include "buffer.h"
#include "stralloc.h"

int
buffer_gettoken(buffer *b, stralloc *sa, char x)
{
	ssize_t r;
	ssize_t n = 0;
	char c;

	stralloc_zero(sa);
	while ((r = buffer_getc(b, &c)) > 0) {
		if (!stralloc_catb(sa, &c, 1)) return -1;
		if (c == x) return 1;
		++n;
	}
	return r;
}
