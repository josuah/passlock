NAME = passlock
VERSION = 0.2

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/man

W = -Wall -Wextra -std=c99 --pedantic
I = -I'${LIBSODIUM}/include' -I'src'
L = -L'${LIBSODIUM}/lib'
D = -D_POSIX_C_SOURCE=200811L -DVERSION='"${VERSION}"'
CFLAGS = $W $I $D -g
LDFLAGS = $W $L -static
LIBS = -static -lsodium -lpthread

SRC = src/util.c src/log.c src/passlock.c
HDR = src/util.h src/log.h src/passlock.h
BIN = passlock-check passlock-debug passlock-set
OBJ = ${SRC:.c=.o}

all: ${BIN}

${BIN}: ${BIN:=.o} ${OBJ}
	${CC} ${LDFLAGS} -o $@ $@.o ${OBJ} ${LIBS}

${BIN:=.o} ${OBJ}: ${HDR} Makefile

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

clean:
	rm -rf ${NAME}-${VERSION} ${BIN} *.o */*.o *.gz

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${BIN} ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f doc/*.1 ${DESTDIR}${MANPREFIX}/man1

dist: clean
	mkdir -p ${NAME}-${VERSION}
	cp -r README Makefile doc src ${BIN:=.c} ${NAME}-${VERSION}
	tar -cf - ${NAME}-${VERSION} | gzip -c >${NAME}-${VERSION}.tar.gz
