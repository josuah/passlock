#include "buffer.h"

int
buffer_fill(buffer *b)
{
	ssize_t r;

	r = b->op(b->fd, b->x + b->n, b->a - b->n);
	if (r <= 0) return 0;
	b->n += r;
	return r;
}
