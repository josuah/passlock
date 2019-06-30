#include "fd.h"
#include <errno.h>
#include <unistd.h>

ssize_t
fd_read(int fd, char *s, size_t n)
{
	ssize_t r;
	while ((r = read(fd, s, n)) == -1 && (errno == EINTR));
	return r;
}
