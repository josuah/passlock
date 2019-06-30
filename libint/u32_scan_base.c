#include "int.h"

size_t
u32_scan_base(u32 *u, char const *s, size_t n, u8 b)
{
	u8 c;
	int r;
	u32 x = 0;
	size_t i;

	r = (UINT32_MAX * b) / b;
	for (i = 0; i < n && u8_scan_base(&c, s[i], b); i++) {
		if (x > UINT32_MAX / b) return 0;
		if (x == UINT32_MAX / b && c >= r) return 0;
		*u = x = x * b + c;
	}
	return i;
}
