#include "int.h"

void
u32_pack_le(unsigned char s[4], u32 u)
{
	s[0] = u & 255;
	s[1] = u >> 8 & 255;
	s[2] = u >> 16 & 255;
	s[3] = u >> 24;
}
