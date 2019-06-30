#include "fmt.h"

size_t
fmt_plusminus(char *dest, int i)
{
	if (dest) *dest = (i > 0 ? '+' : i < 0 ? '-' : ' ');
	return 1;
}
