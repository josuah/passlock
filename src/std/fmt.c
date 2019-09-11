#include "std/fmt.h"

#include "std/int.h"
#include "std/str.h"

size_t
fmt_u(char *s, u64 u, u8 b)
{
	size_t n = 0;
	u64 x;

	x = u; do { x /= b; ++n; } while (x);
	if (!s) return n;

	s += n;
	x = u; do { *--s = '0' + x % b; x /= b; } while (x);
	return n;
}

size_t
fmt_i(char *s, i64 i, u8 b)
{
	if (i < 0) {
		if (s) *s++ = '-';
		return fmt_u(s, (u64)-i, b) + 1;
	} else {
		return fmt_u(s, (u64)i, b);
	}
}

size_t
fmt_u0(char *s, u64 i, size_t pad, u8 b)
{
	size_t n = 1;
	u64 x;

	x = i; while (x + 1 > b) { x /= b; ++n; }
	if (!s) return pad > n ? pad : n;

	while (n < pad) { *s++ = '0'; ++n; }
	fmt_u(s, i, b);
	return n;
}

size_t
fmt_minus(char *s, int i)
{
	if (i >= 0) return 0;
	if (s) *s = '-';
	return 1;
}

size_t
fmt_pad(char *d, size_t size, char const *s, size_t pad)
{
	size_t n = 0;
	size_t max;
	size_t slen = str_len(s);

	if (!d) return slen > pad ? slen : pad;

	max = size < pad + slen ? size : pad + slen;
	while (n++ < pad - slen) *d++ = ' ';
	while (n++ < max) *d++ = *s++;

	return n;
}

size_t
fmt_plusminus(char *d, int i)
{
	if (d) *d = (i > 0 ? '+' : i < 0 ? '-' : ' ');
	return 1;
}

size_t
fmt_xmem(char const *s, size_t n, char *d)
{
	char *ascii = "0123456789abcdef";

	if (!d) return n * 2;

	for (size_t i = 0; i < n; ++i) {
		d[i * 2]     = ascii[(unsigned char)s[i] >> 4];
		d[i * 2 + 1] = ascii[(unsigned char)s[i] & 0x0f];
	}

	return n * 2;
}
