#include "int.h"

u16
u16_unpack_le(const unsigned char s[2])
{
	u16 x = (unsigned char)s[0];
	x |= (u16)(unsigned char)s[1] << 8;
	return x;
}
