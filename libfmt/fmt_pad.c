#include "fmt.h"

#include "str.h"

size_t
fmt_pad(char *dest, size_t size, char const *src, size_t pad)
{
	size_t n = 0;
	size_t max;
	size_t srclen = str_len(src);

	if (!dest) return srclen > pad ? srclen : pad;

	max = size < pad + srclen ? size : pad + srclen;
	while (n++ < pad - srclen) *dest++ = ' ';
	while (n++ < max) *dest++ = *src++;

	return n;
}
