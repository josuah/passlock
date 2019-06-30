#include "buffer.h"

#include "mem.h"

int
buffer_put(buffer *b, const char *s, size_t n)
{
	if (n > b->a - b->n) if (buffer_flush(b) <= 0) return 0;
	if (n > b->a) return (size_t)b->op(b->fd, s, n) == n;
	mem_copy(b->x + b->n, s, n);
	b->n += n;
	return 1;
}
