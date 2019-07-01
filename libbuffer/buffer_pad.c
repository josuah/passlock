#include "buffer.h"
#include "str.h"

int
buffer_pad(buffer *b, char const *s, size_t n, char c)
{
	size_t i;

	for (i = str_len(s); i < n; i++)
		if (!buffer_putc(b, c)) return 0;
	return 1;
}
