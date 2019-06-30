#include "int.h"

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
