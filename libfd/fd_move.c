#include "fd.h"

int
fd_move(int from, int to)
{
	int e;

	if ((e = fd_copy(from, to)) == -1) return -1;
	if (fd_close(from) == -1) return -1;

	return e;
}
