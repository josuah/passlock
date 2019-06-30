#include "mem.h"

void
mem_xor(unsigned char *out, const unsigned char *in, size_t n)
{
	for (size_t i = 0; i < n; i++) out[i] ^= in[i];
}
