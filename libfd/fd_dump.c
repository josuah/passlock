#include "fd.h"
#include <unistd.h>

int
fd_dump(int fd_to, int fd_from)
{
	char s[1024];
	ssize_t n;

	while ((n = fd_read(fd_from, s, sizeof s)) > 0)
		if (fd_write(fd_to, s, n) < n) return -1;
	return n;
}
