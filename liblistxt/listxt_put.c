#include "listxt.h"
#include "buffer.h"
#include <errno.h>

int
listxt_put(buffer *b, genalloc *ga)
{
	size_t i;

	for (i = 0; i < genalloc_len(char *, ga); i++) {
		if (i > 0) if (!buffer_puts(b, ":")) return 0;
		if (!buffer_puts(b, genalloc_s(char *, ga)[i])) return 0;
	}
	if (!buffer_puts(b, "\n")) return 0;
	return 1;
}
