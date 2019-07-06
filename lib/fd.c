#include "fd.h"
#include <errno.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int
fd_chdir(int fd)
{
	int e;
	while ((e = fchdir(fd)) == -1 && (errno != EINTR));
	return e;
}

int
fd_chmod(int fd, mode_t mode)
{
	int e;
	while ((e = fchmod(fd, mode)) == -1 && (errno != EINTR));
	return e;
}

int
fd_chown(int fd, uid_t uid, gid_t gid)
{
	int e;
	while ((e = fchown(fd, uid, gid)) == -1 && (errno != EINTR));
	return e;
}

int
fd_close(int fd)
{
	int e;
	while ((e = close(fd)) == -1 && (errno != EINTR));
	return e;
}

int
fd_copy(int from, int to)
{
	int e;
	while ((e = dup2(from, to)) == -1 && (errno == EINTR)) ;
	return e;
}

int
fd_move(int from, int to)
{
	int e;

	if ((e = fd_copy(from, to)) == -1) return -1;
	if (fd_close(from) == -1) return -1;

	return e;
}

ssize_t
fd_read(int fd, char *s, size_t n)
{
	ssize_t r;
	while ((r = read(fd, s, n)) == -1 && (errno == EINTR));
	return r;
}

ssize_t
fd_recv(int fd, char *s, size_t n, int flags)
{
	int r;
	while ((r = recv(fd, s, n, flags)) == -1 && (errno != EINTR));
	return r;
}

ssize_t
fd_send(int fd, char *s, size_t n, int flags)
{
	int w;
	while ((w = send(fd, s, n, flags)) == -1 && (errno != EINTR));
	return w;
}

ssize_t
fd_write(int fd, char *s, size_t n)
{
	ssize_t w;
	while ((w = write(fd, s, n)) == -1 && (errno != EINTR));
	return w;
}
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
