#include "int.h"

u32
u32_unpack_le(const unsigned char s[4])
{
	u32 x = (unsigned char)s[0];
	x |= (u32)(unsigned char)s[1] << 8;
	x |= (u32)(unsigned char)s[2] << 16;
	x |= (u32)(unsigned char)s[3] << 24;
	return x;
}
