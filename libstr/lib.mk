libstr/str_chr.o:              libstr/str_chr.c               include/str.h
libstr/str_rchr.o:             libstr/str_rchr.c              include/str.h

libstr = libstr/str_chr.o libstr/str_rchr.o
libstr.a: ${libstr}
	rm -f ${@}
	${AR} rc ${@} ${libstr}
	ranlib ${@}
