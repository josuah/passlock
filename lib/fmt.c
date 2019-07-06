#include "str.h"
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


size_t
fmt_fill(char *dest, size_t size, char const *src, size_t fill)
{
	size_t n = 0;
	size_t max;
	size_t srclen = str_len(src);

	if (!dest) return srclen > fill ? srclen : fill;

	max = size < srclen ? size : srclen;
	while (n < max) dest[n++] = *src++;
	while (n < fill) dest[n++] = ' ';

	return n;
}

size_t
fmt_long(char *dest, long i)
{
	if (i < 0) {
		if (dest) *dest++ = '-';
		return fmt_ulong(dest, (unsigned long) -i) + 1;
	} else {
		return fmt_ulong(dest, (unsigned long) i);
	}
}

size_t
fmt_minus(char *dest, int i)
{
	if (i >= 0) return 0;
	if (dest) *dest = '-';
	return 1;
}


size_t
fmt_pad(char *dest, size_t size, char const *src, size_t pad)
{
	size_t n = 0;
	size_t max;
	size_t srclen = str_len(src);

	if (!dest) return srclen > pad ? srclen : pad;

	max = size < pad + srclen ? size : pad + srclen;
	while (n++ < pad - srclen) *dest++ = ' ';
	while (n++ < max) *dest++ = *src++;

	return n;
}

size_t
fmt_plusminus(char *dest, int i)
{
	if (dest) *dest = (i > 0 ? '+' : i < 0 ? '-' : ' ');
	return 1;
}


size_t
fmt_strn(char *dest, size_t n, char const *src)
{
	size_t len;

	if (*dest) return str_copy(dest, src, n);
	len = str_len(src);
	return n < len ? n : len;
}

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
