#include "fmt.h"

size_t
fmt_ulong(char *buf, unsigned long i)
{
	size_t n = 0;
	unsigned long x;

	x = i; do { x /= 10; ++n; } while (x);
	if (!buf) return n;

	buf += n;
	x = i; do { *--buf = '0' + x % 10; x /= 10; } while (x);
	return n;
}
