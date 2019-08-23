#ifndef STD_OPEN_H
#define STD_OPEN_H

#include <fcntl.h>
#include "std/stralloc.h"

#define open_append(path)   open(path, O_WRONLY | O_NONBLOCK | O_APPEND | O_CREAT, 0600)
#define open_excl(path)     open(path, O_WRONLY | O_EXCL | O_CREAT, 0600)
#define open_read(path)     open(path, O_RDONLY | O_NONBLOCK)
#define open_truncate(path) open(path, O_WRONLY | O_NONBLOCK | O_TRUNC | O_CREAT, 0600)
#define open_write(path)    open(path, O_WRONLY | O_NDELAY)

int             open_read_close(char const *, struct stralloc *, size_t);
int             open_write_close(char const *, char const *, size_t);

#endif
