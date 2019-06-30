#include "buffer.h"
#include "fmt.h"

int
buffer_putn(buffer *b, unsigned long ul)
{
	char num[30];

	return buffer_put(b, num, fmt_ulong(num, ul));
}
