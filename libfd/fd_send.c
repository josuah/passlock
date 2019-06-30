#include "fd.h"
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

ssize_t
fd_send(int fd, char *s, size_t n, int flags)
{
	int w;
	while ((w = send(fd, s, n, flags)) == -1 && (errno != EINTR));
	return w;
}
