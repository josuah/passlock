#include "fd.h"
#include <errno.h>
#include <unistd.h>

ssize_t
fd_write(int fd, char *s, size_t n)
{
	ssize_t w;
	while ((w = write(fd, s, n)) == -1 && (errno != EINTR));
	return w;
}
