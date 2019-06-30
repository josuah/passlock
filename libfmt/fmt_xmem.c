#include "fmt.h"

size_t
fmt_xmem(char const *buf, size_t n, char *dest)
{
	char *ascii = "0123456789abcdef";

	if (!dest) return n * 2;

	for (size_t i = 0; i < n; ++i) {
		dest[i * 2]     = ascii[(unsigned char)buf[i] >> 4];
		dest[i * 2 + 1] = ascii[(unsigned char)buf[i] & 0x0f];
	}

	return n * 2;
}
