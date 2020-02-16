#include "base64.h"

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

static int8_t base64_char[256] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1,  0, -1, -1, 
	-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, 
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
};

void
base64_encode(char const *s, size_t sn, char *d)
{
	char base64_symbol[64] = 
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef"
		"ghijklmnopqrstuvwxyz0123456789+/";
	size_t si = 0, di = 0;
	uint64_t x;

	for (si = 0; si < sn; si++) {
		switch (si % 3) {
		case 0:
			/* AAAAAABB bbbbcccc ccdddddd */
			d[di++] = base64_symbol[s[si] >> 2];
			x = s[si] << 4 & 0x3f;
			break;
		case 1:
			/* aaaaaabb BBBBCCCC ccdddddd */
			d[di++] = base64_symbol[x | (s[si] >> 4)];
			x = (s[si] << 2) & 0x3f;
			break;
		case 2:
			/* aaaaaabb bbbbcccc CCDDDDDD */
			d[di++] = base64_symbol[x | (s[si] >> 6)];
			d[di++] = base64_symbol[s[si] & 0x3f];
			break;
		}
	}

	if (si % 3 < 2) d[di++] = base64_symbol[x];

	while (di % 4 != 0) d[di++] = '=';
}

size_t
base64_decode(char const *s, size_t sn, char *d, size_t *dn)
{
	size_t si = 0;
	size_t di = 0;

	sn -= sn % 4;
	while (si < sn) {
		char c0 = s[si++]; int8_t x0 = base64_char[(unsigned)c0];
		char c1 = s[si++]; int8_t x1 = base64_char[(unsigned)c1];
		char c2 = s[si++]; int8_t x2 = base64_char[(unsigned)c2];
		char c3 = s[si++]; int8_t x3 = base64_char[(unsigned)c3];
		uint32_t x = (x0 << 18) | (x1 << 12) | (x2 << 6) | (x3 << 0);

		/* only "xxxx" or "xxx=" or "xx==" allowed  */
		if (c0 == '=' || c1 == '=' || (c2 == '=' && c3 != '=')) break;
		if (x0 == -1 || x1 == -1 || x2 == -1 || x3 == -1) break;

		d[di++] = x >> 16;
		d[di++] = x >> 8 & 0xff;
		d[di++] = x & 0xff;

		if (c2 == '=') di--;
		if (c3 == '=') { di--; break; }
	}

	*dn = di;
	return si;
}
