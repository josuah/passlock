#include "buffer.h"

int
buffer_get(buffer *b, char *s, size_t n)
{
	ssize_t r;

	r = buffer_getnofill(b, s, n);
	n -= r;
	s += r;
	if (n == 0) return 1;
	if (n > b->a) return (size_t)b->op(b->fd, s, n) == n;
	if ((size_t)buffer_fill(b) < n) return 0;
	buffer_getnofill(b, s, n);
	return 1;
}
