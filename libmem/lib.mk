libmem/mem_chr.o:              libmem/mem_chr.c               include/mem.h
libmem/mem_mem.o:              libmem/mem_mem.c               include/mem.h
libmem/mem_xor.o:              libmem/mem_xor.c               include/mem.h

libmem = libmem/mem_chr.o libmem/mem_mem.o libmem/mem_xor.o
libmem.a: ${libmem}
	rm -f ${@}
	${AR} rc ${@} ${libmem}
	ranlib ${@}
