#include "int.h"

void
u16_pack_le(unsigned char s[2], u16 u)
{
	s[0] = u & 255;
	s[1] = u >> 8;
}
