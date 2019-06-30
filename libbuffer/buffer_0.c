#include "buffer.h"
#include "fd.h"
#include <unistd.h>

static char buffer_0_buf[8192];
buffer buffer_0[1] = { BUFFER_INIT(fd_read, 0, buffer_0_buf, sizeof buffer_0_buf) };
