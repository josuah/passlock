#include "fd.h"
#include <errno.h>
#include <sys/stat.h>

int
fd_chmod(int fd, mode_t mode)
{
	int e;
	while ((e = fchmod(fd, mode)) == -1 && (errno != EINTR));
	return e;
}
