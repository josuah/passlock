#include "fmt.h"

size_t
fmt_ulong0(char *dest, unsigned long i, size_t pad)
{
	size_t n = 1;
	unsigned long x;

	x = i; while (x > 9) { x /= 10; ++n; }
	if (!dest) return pad > n ? pad : n;

	while (n <= pad) { *dest++ = '0'; ++n; }
	fmt_ulong(dest, i);
	return n;
}
