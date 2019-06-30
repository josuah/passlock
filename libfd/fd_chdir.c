#include "fd.h"
#include <errno.h>
#include <unistd.h>

int
fd_chdir(int fd)
{
	int e;
	while ((e = fchdir(fd)) == -1 && (errno != EINTR));
	return e;
}
