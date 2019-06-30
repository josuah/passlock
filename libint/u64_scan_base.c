#include "int.h"

size_t
u64_scan_base(u64 *u, char const *s, size_t n, u8 b)
{
	u8 c;
	int r;
	u64 x = 0;
	size_t i;

	r = (UINT64_MAX * b) / b;
	for (i = 0; i < n && u8_scan_base(&c, s[i], b); i++) {
		if (x > UINT64_MAX / b) return 0;
		if (x == UINT64_MAX / b && c >= r) return 0;
		*u = x = x * b + c;
	}
	return i;
}
