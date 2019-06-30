#include "fmt.h"

size_t
fmt_8long(char *buf, unsigned long i)
{
	size_t n = 0;
	unsigned long x;

	x = i; do { x >>= 3; ++n; } while (x);
	if (!buf) return n;

	buf += n;
	x = i; do { *--buf = (x & 7) + '0'; x >>= 3; } while (x);
	return n;
}
