#ifndef FD_H
#define FD_H

#include <unistd.h>
#include <sys/stat.h>

// bin/make-h lib/fd.c
int     fd_chdir(int);
int     fd_chmod(int, mode_t);
int     fd_chown(int, uid_t, gid_t);
int     fd_close(int);
int     fd_copy(int, int);
int     fd_dump(int, int);
int     fd_move(int, int);
ssize_t fd_read(int, char *, size_t);
ssize_t fd_recv(int, char *, size_t, int);
ssize_t fd_send(int, char *, size_t, int);
ssize_t fd_write(int, char *, size_t);

#endif
