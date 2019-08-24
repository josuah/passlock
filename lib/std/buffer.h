#ifndef STD_BUFFER_H
#define STD_BUFFER_H

#include "std/int.h"
#include "std/str.h"
#include "std/stralloc.h"
#include <stddef.h>
#include <unistd.h>

struct buffer {
	char *x;
	size_t a;  // allocated size, 0 means fd closed
	size_t n;  // used size
	size_t p;  // position (read buffer only)
	int fd;
	ssize_t (*op)();
};

#define BUFFER_INIT(op, fd, x, n) { (x), (n), (0), (0), (fd), (op) }

extern struct buffer buffer_0[1];
extern struct buffer buffer_1[1];
extern struct buffer buffer_2[1];

#define buffer_puts(b, s)     buffer_put(b, s, str_len(s))
#define buffer_getc(b, p)     buffer_get(b, p, 1)
#define buffer_getline(b, sa) buffer_gettoken(b, sa, '\n')

int             buffer_dump(int, int);
int             buffer_flush(struct buffer *);
int             buffer_get(struct buffer *, char *, size_t);
int             buffer_gettoken(struct buffer *, struct stralloc *, char);
int             buffer_pad(struct buffer *, char const *, char *, size_t);
int             buffer_put(struct buffer *, const char *, size_t);
int             buffer_putc(struct buffer *, char);
int             buffer_putn(struct buffer *, unsigned long);
int             buffer_ungetc(struct buffer *, char);
size_t          buffer_fill(struct buffer *);
ssize_t         buffer_read(int, char *, size_t);
ssize_t         buffer_write(int, char *, size_t);
void            buffer_init(struct buffer *, ssize_t (*op)(), int, char *, size_t);

#endif
