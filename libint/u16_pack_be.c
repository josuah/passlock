#include "int.h"

void
u16_pack_be(unsigned char s[2], u16 u)
{
	s[1] = u & 255;
	s[0] = u >> 8;
}
