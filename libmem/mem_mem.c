#include "mem.h"

size_t
mem_mem(char const *buf1, size_t n1, char const *buf2, size_t n2)
{
	for (size_t i = 0; i + n2 <= n1; ++i)
		if (mem_equal(buf1 + i, buf2, n2)) return i;
	return n1;
}
