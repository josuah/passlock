#include "fmtnum.h"

#include <stdint.h>

char *
fmtnum(char *num, intmax_t n)
{
	intmax_t i;
	char *out;

	out = num;
	if (n < 0) {
		*num++ = '-';
		n = -n;
	}
	for (i = n; i; i /= 10)
		++num;
	for (i = n; i; i /= 10)
		*--num = '0' + i % 10;
	return out;
}
