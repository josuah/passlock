#include "buffer.h"

#include "mem.h"

size_t
buffer_getnofill(buffer *b, char *buf, size_t n)
{
	if (n > b->n - b->p) n = b->n - b->p;
	mem_copy(buf, b->x + b->p, n);
	b->p += n;
	if (b->p == b->n) b->p = b->n = 0;
	return n;
}
