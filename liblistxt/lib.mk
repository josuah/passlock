liblistxt/listxt_get.o:        liblistxt/listxt_get.c         include/listxt.h include/buffer.h include/open.h include/stralloc.h
liblistxt/listxt_getline.o:    liblistxt/listxt_getline.c     include/listxt.h include/str.h
liblistxt/listxt_put.o:        liblistxt/listxt_put.c         include/listxt.h include/buffer.h
liblistxt/listxt_scan.o:       liblistxt/listxt_scan.c        include/listxt.h include/str.h
liblistxt/listxt_tmp.o:        liblistxt/listxt_tmp.c         include/listxt.h include/stralloc.h include/fmt.h
liblistxt/listxt_valid.o:      liblistxt/listxt_valid.c       include/listxt.h include/str.h

liblistxt = liblistxt/listxt_get.o liblistxt/listxt_getline.o liblistxt/listxt_put.o liblistxt/listxt_scan.o liblistxt/listxt_tmp.o liblistxt/listxt_valid.o
liblistxt.a: ${liblistxt}
	rm -f ${@}
	${AR} rc ${@} ${liblistxt}
	ranlib ${@}
