#include "listxt.h"
#include "buffer.h"
#include "stralloc.h"
#include "arg.h"

int
listxt_get(char *path, stralloc *sa, genalloc *ga, size_t n, char *s)
{
	char bx[1024];
	buffer b = BUFFER_INIT(read, 0, bx, sizeof bx);

	if ((b.fd = open_read(path)) == -1) return 0;

	while (stralloc_zero(sa), listxt_getline(b, sa, ga)) {
		if (genalloc_len(char *, ga) < n) continue;
		if (str_equal(genalloc_s(char *, ga)[n], s)) return 1;
	}

	return 0;
}
