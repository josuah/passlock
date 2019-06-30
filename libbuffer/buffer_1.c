#include "buffer.h"
#include "fd.h"
#include <unistd.h>

static char buffer_1_buf[8192];
buffer buffer_1[1] = { BUFFER_INIT(fd_write, 1, buffer_1_buf, sizeof buffer_1_buf) };
