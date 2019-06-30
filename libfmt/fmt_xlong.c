#include "fmt.h"

size_t
fmt_xlong(char *buf, unsigned long u)
{
	size_t n = 0;
	unsigned long x;
	char *ascii = "0123456789abcdef";

	x = u; do { x >>= 4; ++n; } while (x);
	if (!buf) return n;

	buf += n;
	x = u; do { *--buf = ascii[x & 15]; x >>= 4; } while (x);
	return n;
}
