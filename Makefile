VERSION = v0.2

LIBSODIUM = ${PREFIX}

W = -Wall -Wextra -std=c99 --pedantic
CFLAGS = $W -I'${LIBSODIUM}/include' -I'lib' -g -DVERSION='"${VERSION}"'
LFLAGS = $W -L'${LIBSODIUM}/lib' -static
LIB = -lsodium #-lpthread

#
bin =	passlist-add passlist-check passlist-del passlist-list

inc =	lib/arg.h lib/buffer.h lib/env.h lib/fmt.h lib/genalloc.h lib/int.h  \
	lib/listxt.h lib/log.h lib/mem.h lib/open.h lib/str.h lib/stralloc.h

obj =	lib/arg.o lib/buffer.o lib/fmt.o lib/int.o lib/listxt.o lib/log.o  \
	lib/mem.o lib/open.o lib/str.o lib/stralloc.o

all: ${bin}

clean:
	rm -f *.a *.o */*.o ${bin}

install: all
	mkdir -p ${PREFIX}/bin
	cp ${bin} ${PREFIX}/bin
	mkdir -p ${PREFIX}/share/man/man1
	cp *.1  ${PREFIX}/share/man/man1
	mkdir -p ${PREFIX}/share/man/man8
	cp *.8  ${PREFIX}/share/man/man8

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

passlist-add: passlist-add.o ${obj} ${inc}
	${CC} ${LFLAGS} -o $@ $@.o ${obj} ${LIB}

passlist-check: passlist-check.o ${obj} ${inc}
	${CC} ${LFLAGS} -o $@ $@.o ${obj} ${LIB}

passlist-del: passlist-del.o ${obj} ${inc}
	${CC} ${LFLAGS} -o $@ $@.o ${obj} ${LIB}

passlist-list: passlist-list.o ${obj} ${inc}
	${CC} ${LFLAGS} -o $@ $@.o ${obj} ${LIB}
