#include "mem.h"

size_t
mem_chr(char const *s, size_t n, char c)
{
	char *p = memchr(s, c, n);
	return (p == NULL) ? n : (size_t)(p - s);
}
