#include "fd.h"
#include <errno.h>
#include <unistd.h>

int
fd_copy(int from, int to)
{
	int e;
	while ((e = dup2(from, to)) == -1 && (errno == EINTR)) ;
	return e;
}
