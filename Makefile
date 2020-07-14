NAME = passlock
VERSION = 0.1

SRC = src/passlock.c src/log.c src/compat/strchomp.c src/compat/strlcpy.c

HDR = src/compat.h src/passlock.h src/log.h

BIN = passlock-check passlock-debug passlock-set

OBJ = ${SRC:.c=.o}

LIB = -lsodium

W = -Wall -Wextra -std=c99 --pedantic
I = -I'${LIBSODIUM}/include' -I'src'
L = -L'${LIBSODIUM}/lib'
D = -D_POSIX_C_SOURCE=200811L -DVERSION='"${VERSION}"'
CFLAGS = $I $D $W -g
LDFLAGS = $L -static
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/man

all: ${BIN}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

${OBJ}: ${HDR}
${BIN}: ${OBJ} ${BIN:=.o}
	${CC} ${LDFLAGS} -o $@ $@.o ${OBJ} ${LIB}

clean:
	rm -rf *.o */*.o ${BIN} ${NAME}-${VERSION} *.gz

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -rf bin/* ${BIN} ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -rf doc/*.1 ${DESTDIR}${MANPREFIX}/man1

dist: clean
	mkdir -p ${NAME}-${VERSION}
	cp -r README Makefile bin doc ${SRC} ${NAME}-${VERSION}
	tar -cf - ${NAME}-${VERSION} | gzip -c >${NAME}-${VERSION}.tar.gz
