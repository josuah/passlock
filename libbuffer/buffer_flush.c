#include "buffer.h"

int
buffer_flush(buffer *b)
{
	ssize_t w = b->n - b->p;

	if (w != b->op(b->fd, b->x + b->p, w)) return 0;
	b->p = b->n = 0;
	return 1;
}
