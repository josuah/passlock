#include "int.h"

void
u32_pack_be(unsigned char s[4], u32 u)
{
	s[3] = u & 255;
	s[2] = u >> 8 & 255;
	s[1] = u >> 16 & 255;
	s[0] = u >> 24;
}
