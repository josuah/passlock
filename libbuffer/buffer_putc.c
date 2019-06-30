#include "buffer.h"

int
buffer_putc(buffer *b, char c)
{
	return buffer_put(b, &c, 1);
}
