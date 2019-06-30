#include "fmt.h"

size_t
fmt_minus(char *dest, int i)
{
	if (i >= 0) return 0;
	if (dest) *dest = '-';
	return 1;
}
