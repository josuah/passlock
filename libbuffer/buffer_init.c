#include "buffer.h"

void
buffer_init(buffer *b, ssize_t (*op)(), int fd, char *s, size_t n)
{
	b->fd = fd;
	b->op = op;
	b->x = s;
	b->a = n;
	b->n = 0;
	b->p = 0;
}
