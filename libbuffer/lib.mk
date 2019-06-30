libbuffer/buffer_0.o:          libbuffer/buffer_0.c           include/buffer.h include/fd.h
libbuffer/buffer_1.o:          libbuffer/buffer_1.c           include/buffer.h include/fd.h
libbuffer/buffer_2.o:          libbuffer/buffer_2.c           include/buffer.h include/fd.h
libbuffer/buffer_fill.o:       libbuffer/buffer_fill.c        include/buffer.h
libbuffer/buffer_flush.o:      libbuffer/buffer_flush.c       include/buffer.h
libbuffer/buffer_get.o:        libbuffer/buffer_get.c         include/buffer.h
libbuffer/buffer_getnofill.o:  libbuffer/buffer_getnofill.c   include/buffer.h include/mem.h
libbuffer/buffer_gettoken.o:   libbuffer/buffer_gettoken.c    include/buffer.h include/stralloc.h
libbuffer/buffer_init.o:       libbuffer/buffer_init.c        include/buffer.h
libbuffer/buffer_put.o:        libbuffer/buffer_put.c         include/buffer.h include/mem.h
libbuffer/buffer_putc.o:       libbuffer/buffer_putc.c        include/buffer.h
libbuffer/buffer_putn.o:       libbuffer/buffer_putn.c        include/buffer.h include/fmt.h

libbuffer = libbuffer/buffer_0.o libbuffer/buffer_1.o libbuffer/buffer_2.o libbuffer/buffer_fill.o libbuffer/buffer_flush.o libbuffer/buffer_get.o libbuffer/buffer_getnofill.o libbuffer/buffer_gettoken.o libbuffer/buffer_init.o libbuffer/buffer_put.o libbuffer/buffer_putc.o libbuffer/buffer_putn.o
libbuffer.a: ${libbuffer}
	rm -f ${@}
	${AR} rc ${@} ${libbuffer}
	ranlib ${@}
