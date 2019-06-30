#include "int.h"

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
