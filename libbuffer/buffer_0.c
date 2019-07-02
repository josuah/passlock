#include "buffer.h"
#include "fd.h"
#include <unistd.h>

static char b0[8192];
buffer buffer_0[1] = { BUFFER_INIT(fd_read, 0, b0, sizeof b0) };
