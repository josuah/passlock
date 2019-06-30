#include "buffer.h"
#include "fd.h"
#include <unistd.h>

static char buffer_2_buf[256];
buffer buffer_2[1] = { BUFFER_INIT(fd_write, 2, buffer_2_buf, sizeof buffer_2_buf) };
