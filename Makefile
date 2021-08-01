NAME = passlock
VERSION = 0.1
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/man

D = -D_POSIX_C_SOURCE=200811L -DVERSION='"${VERSION}"'
CFLAGS = -g -Wall -Wextra -std=c99 --pedantic -fPIC $D -I'${LIBSODIUM}/include'
LDFLAGS = -static -L'${LIBSODIUM}/lib'

SRC = passlock.c util.c
HDR = passlock.h util.h
BIN = passlock-check passlock-debug passlock-set
OBJ = ${SRC:.c=.o}
LIB = -lsodium
MAN1 = passlock.1

all: ${BIN}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

${OBJ} ${BIN:=.o}: Makefile ${HDR}

${BIN}: ${OBJ} ${BIN:=.o}
	${CC} ${LDFLAGS} -o $@ $@.o ${OBJ} ${LIB}

clean:
	rm -rf *.o ${BIN} ${NAME}-${VERSION} *.tgz

install: ${BIN}
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${BIN} ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f ${MAN1} ${DESTDIR}${MANPREFIX}/man1

dist:
	git archive v${VERSION} --prefix=${NAME}-${VERSION}/ \
	| gzip >${NAME}-${VERSION}.tgz

site:
	notmarkdown README.md | notmarkdown-html | cat .head.html - >index.html
	notmarkdown README.md | notmarkdown-gph | cat .head.gph - >index.gph
	mkdir -p man
	mandoc -Thtml -Ofragment ${MAN1} | cat .head.html - >man/index.html
	mandoc -Tutf8 ${MAN1} | ul -t dumb >man/index.gph
	sed -i "s/NAME/${NAME}/g; s/VERSION/${VERSION}/g" index.* man/index.*
