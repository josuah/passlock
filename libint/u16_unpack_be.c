#include "int.h"

u16
u16_unpack_be(const unsigned char s[2])
{
	u16 x = (unsigned char)s[1];
	x |= (u16)(unsigned char)s[0] << 8;
	return x;
}
