#include "fmt.h"

#include "str.h"

size_t
fmt_strn(char *dest, size_t n, char const *src)
{
	size_t len;

	if (*dest) return str_copy(dest, src, n);
	len = str_len(src);
	return n < len ? n : len;
}
