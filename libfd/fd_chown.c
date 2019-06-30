#include "fd.h"
#include <errno.h>
#include <unistd.h>

int
fd_chown(int fd, uid_t uid, gid_t gid)
{
	int e;
	while ((e = fchown(fd, uid, gid)) == -1 && (errno != EINTR));
	return e;
}
