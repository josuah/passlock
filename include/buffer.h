#ifndef BUFFER_H
#define BUFFER_H

#include "int.h"
#include "str.h"
#include "stralloc.h"
#include <stddef.h>
#include <unistd.h>

typedef struct {
	char *x;
	size_t a;  // allocated size, 0 means fd closed
	size_t n;  // used size
	size_t p;  // position (read buffer only)
	int fd;
	ssize_t (*op)();
} buffer;

#define BUFFER_INIT(op, fd, x, n) { (x), (n), (0), (0), (fd), (op) }

extern buffer buffer_0[1];
extern buffer buffer_1[1];
extern buffer buffer_2[1];

#define buffer_puts(b, s)     buffer_put(b, s, str_len(s))
#define buffer_getc(b, p)     buffer_get(b, p, 1)
#define buffer_getline(b, sa) buffer_gettoken(b, sa, '\n')

// bin/make-h libbuffer/*.c
int     buffer_fill(buffer *);
int     buffer_flush(buffer *);
int     buffer_get(buffer *, char *, size_t);
int     buffer_gettoken(buffer *, stralloc *, char);
int     buffer_put(buffer *, const char *, size_t);
int     buffer_putc(buffer *, char);
int     buffer_putn(buffer *, unsigned long);
size_t  buffer_getnofill(buffer *, char *, size_t);
void    buffer_init(buffer *, ssize_t (*op)(), int, char *, size_t);

#endif
