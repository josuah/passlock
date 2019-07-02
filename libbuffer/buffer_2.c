#include "buffer.h"
#include "fd.h"
#include <unistd.h>

static char b2[256];
buffer buffer_2[1] = { BUFFER_INIT(fd_write, 2, b2, sizeof b2) };
