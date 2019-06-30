#include "fmt.h"

size_t
fmt_xlong0(char *buf, unsigned long i, size_t pad)
{
	size_t n = 0;
	unsigned long x = i;

	do { x >>= 4; ++n; } while (x > 15);
	if (!buf) return pad > n ? pad : n;

	while (n < pad) { *buf++ = '0'; ++n; }
	if (buf) fmt_xlong(buf, i);
	return n;
}
