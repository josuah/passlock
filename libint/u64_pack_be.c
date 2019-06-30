#include "int.h"

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
