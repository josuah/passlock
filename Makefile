NAME = passlock
VERSION = 0.1

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

all: ${BIN}

${BIN}: ${BIN:=.o} ${OBJ} ${HDR}
	${CC} ${LFLAGS} -o $@ $@.o ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

clean:
	rm -f *.a *.o */*.o *.gz ${BIN}

dist:
	rm -rf ${NAME}-${VERSION}
	mkdir -p ${NAME}-${VERSION}/src
	cp -r README Makefile doc ${BIN:=.c} ${NAME}-${VERSION}
	cp src/*.[ch] ${NAME}-${VERSION}/src
	tar -cf - ${NAME}-${VERSION} | gzip -c >${NAME}-${VERSION}.tar.gz

install: ${BIN}
	mkdir -p ${DESTDIR}${PREFIX}/BIN
	cp -f ${BIN} ${DESTDIR}${PREFIX}/BIN
	mkdir -p ${DESTDIR}${PREFIX}/share/man/man1
	cp -f doc/*.1 ${DESTDIR}${PREFIX}/share/man/man1
