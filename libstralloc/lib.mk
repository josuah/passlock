libstralloc/stralloc_catb.o:   libstralloc/stralloc_catb.c    include/stralloc.h include/mem.h
libstralloc/stralloc_catc.o:   libstralloc/stralloc_catc.c    include/stralloc.h
libstralloc/stralloc_chomp.o:  libstralloc/stralloc_chomp.c   include/stralloc.h
libstralloc/stralloc_free.o:   libstralloc/stralloc_free.c    include/stralloc.h
libstralloc/stralloc_ready.o:  libstralloc/stralloc_ready.c   include/stralloc.h

libstralloc = libstralloc/stralloc_catb.o libstralloc/stralloc_catc.o libstralloc/stralloc_chomp.o libstralloc/stralloc_free.o libstralloc/stralloc_ready.o
libstralloc.a: ${libstralloc}
	rm -f ${@}
	${AR} rc ${@} ${libstralloc}
	ranlib ${@}
