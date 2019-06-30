#include "int.h"

size_t
u16_scan_base(u16 *u, char const *s, size_t n, u8 b)
{
	u8 c;
	int r;
	u16 x = 0;
	size_t i;

	r = (UINT16_MAX * b) / b;
	for (i = 0; i < n && u8_scan_base(&c, s[i], b); i++) {
		if (x > UINT16_MAX / b) return 0;
		if (x == UINT16_MAX / b && c >= r) return 0;
		*u = x = x * b + c;
	}
	return i;
}
