NAME = passlock
VERSION = 0.1

SRC = passlock.c util.c
HDR = passlock.h util.h
MAN1 = passlock.1
BIN = passlock-check passlock-debug passlock-set
OBJ = ${SRC:.c=.o}
LIB = -lsodium

CFLAGS = -g -D_POSIX_C_SOURCE=200811L -DVERSION='"${VERSION}"' \
	-I'${LIBSODIUM}/include' \
	-Wall -Wextra -std=c99 --pedantic
LDFLAGS = -L'${LIBSODIUM}/lib' -static

PREFIX = /usr/local
MANPREFIX = ${PREFIX}/man

all: ${BIN}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

${OBJ}: ${HDR}
${BIN}: ${OBJ} ${BIN:=.o}
	${CC} ${LDFLAGS} -o $@ $@.o ${OBJ} ${LIB}

clean:
	rm -rf *.o ${BIN} ${NAME}-${VERSION} *.gz

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -rf ${BIN} ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -rf *.1 ${DESTDIR}${MANPREFIX}/man1

dist: clean
	mkdir -p ${NAME}-${VERSION}
	cp -r README.md Makefile *.[ch] ${MAN1} ${NAME}-${VERSION}
	tar -cf - ${NAME}-${VERSION} | gzip -c >${NAME}-${VERSION}.tar.gz

site: dist
	notmarkdown README.md | notmarkdown-html | cat .site/head.html - >index.html
	notmarkdown README.md | notmarkdown-gph | cat .site/head.gph - >index.gph
	cp .site/style.css style.css
