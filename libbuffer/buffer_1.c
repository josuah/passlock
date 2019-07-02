#include "buffer.h"
#include "fd.h"
#include <unistd.h>

static char b1[8192];
buffer buffer_1[1] = { BUFFER_INIT(fd_write, 1, b1, sizeof b1) };
