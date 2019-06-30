#include "fd.h"
#include <errno.h>
#include <unistd.h>

int
fd_close(int fd)
{
	int e;
	while ((e = close(fd)) == -1 && (errno != EINTR));
	return e;
}
