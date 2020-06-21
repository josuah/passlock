NAME = passlock
VERSION = 0.2

SRC = src/log.c src/util.c
HDR = src/util.h src/log.h
BIN = passlock-check passlock-debug passlock-set
OBJ = ${SRC:.c=.o}

W = -Wall -Wextra -std=c99 --pedantic
I = -I'${LIBSODIUM}/include' -I'src'
L = -L'${LIBSODIUM}/lib'
D = -D_POSIX_C_SOURCE=200811L -DVERSION='"${VERSION}"'
CFLAGS = $W $I $D -g
LFLAGS = $W $L
LIBS = -static -lsodium -lpthread
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/man

all: ${BIN}

${BIN}: ${BIN:=.o} ${OBJ} ${HDR}
	${CC} ${LFLAGS} -o $@ $@.o ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

clean:
	rm -rf ${NAME}-${VERSION} ${BIN} *.o */*.o *.gz

install: all
	mkdir -p ${DESTDIR}${PREFIX}/BIN
	cp -f ${BIN} ${DESTDIR}${PREFIX}/BIN
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f doc/*.1 ${DESTDIR}${MANPREFIX}/man1

dist: clean
	mkdir -p ${NAME}-${VERSION}
	cp -r README Makefile doc src ${BIN:=.c} ${NAME}-${VERSION}
	tar -cf - ${NAME}-${VERSION} | gzip -c >${NAME}-${VERSION}.tar.gz
