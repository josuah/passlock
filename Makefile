VERSION = v0.2

LIBSODIUM = ${PREFIX}

W = -Wall -Wextra -std=c99 --pedantic
CFLAGS = $W -I'${LIBSODIUM}/include' -I'lib' -g -DVERSION='"${VERSION}"'
LFLAGS = $W -L'${LIBSODIUM}/lib' -static
LIB = -lsodium -lpthread

bin =	cmd/passlist-check cmd/passlist-del cmd/passlist-list  \
	cmd/passlist-add 

inc =	lib/std/base64.h lib/std/stralloc.h lib/std/str.h lib/std/arg.h  \
	lib/std/int.h lib/std/genalloc.h lib/std/range.h lib/std/test.h  \
	lib/std/listxt.h lib/std/mem.h lib/std/log.h lib/std/clock.h  \
	lib/std/env.h lib/std/open.h lib/std/fmt.h lib/std/buffer.h  \
	lib/std/case.h 

obj =	lib/std/log.o lib/std/base64.o lib/std/fmt.o lib/std/arg.o  \
	lib/std/mem.o lib/std/listxt.o lib/std/case.o lib/std/test.o  \
	lib/std/open.o lib/std/stralloc.o lib/std/int.o lib/std/str.o  \
	lib/std/buffer.o lib/std/range.o 

all: ${bin}

${bin}: ${obj}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

clean:
	rm -f *.a *.o */*.o */*/*.o ${bin}

install: all
	mkdir -p ${PREFIX}/bin
	cp ${bin} ${PREFIX}/bin
	mkdir -p ${PREFIX}/share/man/man1
	cp -f doc/*.1  ${PREFIX}/share/man/man1
	mkdir -p ${PREFIX}/share/man/man8
	cp -f doc/*.8  ${PREFIX}/share/man/man8

.PHONY: test
test: ${obj}
	bin/t >test.c
	${CC} ${CFLAGS} ${LFLAGS} -o $@ test.c ${obj}
	./test

${bin}: ${bin:=.o} ${obj} ${inc}
	${CC} ${LFLAGS} -o $@ $@.o ${obj} ${LIB}
