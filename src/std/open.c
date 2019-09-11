#include "std/open.h"

#include "std/stralloc.h"
#include <errno.h>
#include <unistd.h>

int
open_read_close(char const *path, struct stralloc *sa, size_t bufsize)
{
	ssize_t r;
	int fd = open_read(path);

	if (fd == -1) return 0;
	do {
		if (!stralloc_readyplus(sa, bufsize)) { close(fd); return 0; }
		r = read(fd, sa->s + sa->n, bufsize);
		if (r == -1) {
			if (errno == EINTR) continue;
			if (errno == EAGAIN) continue;
			if (errno == EWOULDBLOCK) continue;
			close(fd);
			return 0;
		}
		sa->n += r;
	} while (r != 0);

	close(fd);
	return 1;
}

int
open_write_close(char const *path, char const *s, size_t n)
{
	ssize_t w;
	int fd = open_write(path);

	if (fd == -1) return 0;
	do {
		w = write(fd, s, n);
		if (w == -1) {
			if (errno == EINTR) continue;
			if (errno == EAGAIN) continue;
			if (errno == EWOULDBLOCK) continue;
			close(fd);
			return 0;
		}
		s += w;
		n -= w;
	} while (n > 0);

	close(fd);
	return 1;
}
