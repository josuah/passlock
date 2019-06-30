#include "fd.h"
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

ssize_t
fd_recv(int fd, char *s, size_t n, int flags)
{
	int r;
	while ((r = recv(fd, s, n, flags)) == -1 && (errno != EINTR));
	return r;
}
