#include "fmt.h"

size_t
fmt_utf8(char *dest, u32 u)
{
	size_t v, n, n2;

	if (u <= 0x7f) {
		if (dest) *dest = u;
		return 1;
	}

	for (v = 0x3f, n = 0; v >= u; ++n) v = (v << 5) | 0x1f;
	if (v >= 0x7fffffff) return 0; /* cannot be encoded */
	if (!dest) return 1 + n;

	*dest++ = (0xff << (7 - n)) | (u >> n * 6);
	for (n2 = n - 1; n2 ; --n2) {
		*dest++ = 0x80 | (u & 0x3f);
		u >>= 6;
	}
	return 1 + n;
}
