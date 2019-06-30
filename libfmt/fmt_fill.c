#include "fmt.h"

#include "str.h"

size_t
fmt_fill(char *dest, size_t size, char const *src, size_t fill)
{
	size_t n = 0;
	size_t max;
	size_t srclen = str_len(src);

	if (!dest) return srclen > fill ? srclen : fill;

	max = size < srclen ? size : srclen;
	while (n < max) dest[n++] = *src++;
	while (n < fill) dest[n++] = ' ';

	return n;
}
