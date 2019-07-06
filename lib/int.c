#include "int.h"

void
u16_pack_be(unsigned char s[2], u16 u)
{
	s[1] = u & 255;
	s[0] = u >> 8;
}

void
u16_pack_le(unsigned char s[2], u16 u)
{
	s[0] = u & 255;
	s[1] = u >> 8;
}

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

u16
u16_unpack_be(const unsigned char s[2])
{
	u16 x = (unsigned char)s[1];
	x |= (u16)(unsigned char)s[0] << 8;
	return x;
}

u16
u16_unpack_le(const unsigned char s[2])
{
	u16 x = (unsigned char)s[0];
	x |= (u16)(unsigned char)s[1] << 8;
	return x;
}

void
u32_pack_be(unsigned char s[4], u32 u)
{
	s[3] = u & 255;
	s[2] = u >> 8 & 255;
	s[1] = u >> 16 & 255;
	s[0] = u >> 24;
}

void
u32_pack_le(unsigned char s[4], u32 u)
{
	s[0] = u & 255;
	s[1] = u >> 8 & 255;
	s[2] = u >> 16 & 255;
	s[3] = u >> 24;
}

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

u32
u32_unpack_be(const unsigned char s[4])
{
	u32 x = (unsigned char)s[3];
	x |= (u32)(unsigned char)s[2] << 8;
	x |= (u32)(unsigned char)s[1] << 16;
	x |= (u32)(unsigned char)s[0] << 24;
	return x;
}

u32
u32_unpack_le(const unsigned char s[4])
{
	u32 x = (unsigned char)s[0];
	x |= (u32)(unsigned char)s[1] << 8;
	x |= (u32)(unsigned char)s[2] << 16;
	x |= (u32)(unsigned char)s[3] << 24;
	return x;
}

void
u64_pack_be(unsigned char s[8], u64 u)
{
	s[7] = u & 255;
	s[6] = u >> 8 & 255;
	s[5] = u >> 16 & 255;
	s[4] = u >> 24 & 255;
	s[3] = u >> 32 & 255;
	s[2] = u >> 40 & 255;
	s[1] = u >> 48 & 255;
	s[0] = u >> 56;
}

void
u64_pack_le(unsigned char s[8], u64 u)
{
	s[0] = u & 255;
	s[1] = u >> 8 & 255;
	s[2] = u >> 16 & 255;
	s[3] = u >> 24 & 255;
	s[4] = u >> 32 & 255;
	s[5] = u >> 40 & 255;
	s[6] = u >> 48 & 255;
	s[7] = u >> 56;
}

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

u64
u64_unpack_be(const unsigned char s[8])
{
	u64 x = (unsigned char)s[7];
	x |= (u64)(unsigned char)s[6] << 8;
	x |= (u64)(unsigned char)s[5] << 16;
	x |= (u64)(unsigned char)s[4] << 24;
	x |= (u64)(unsigned char)s[3] << 32;
	x |= (u64)(unsigned char)s[2] << 40;
	x |= (u64)(unsigned char)s[1] << 48;
	x |= (u64)(unsigned char)s[0] << 56;
	return x;
}

u64
u64_unpack_le(const unsigned char s[8])
{
	u64 x = (unsigned char)s[0];
	x |= (u64)(unsigned char)s[1] << 8;
	x |= (u64)(unsigned char)s[2] << 16;
	x |= (u64)(unsigned char)s[3] << 24;
	x |= (u64)(unsigned char)s[4] << 32;
	x |= (u64)(unsigned char)s[5] << 40;
	x |= (u64)(unsigned char)s[6] << 48;
	x |= (u64)(unsigned char)s[7] << 56;
	return x;
}

int
u8_scan_base(u8 *u, char c, u8 base)
{
	static i8 num[256] = {
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1, 
		-1, 10, 11, 12, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
		25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1, 
		-1, 10, 11, 12, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
		25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1, 
	};

	*u = num[(int)c];
	return num[(int)c] >= 0 && num[(int)c] < base;
}
