libopen/open_read_close.o:     libopen/open_read_close.c      include/open.h include/stralloc.h
libopen/open_write_close.o:    libopen/open_write_close.c     include/open.h

libopen = libopen/open_read_close.o libopen/open_write_close.o
libopen.a: ${libopen}
	rm -f ${@}
	${AR} rc ${@} ${libopen}
	ranlib ${@}
