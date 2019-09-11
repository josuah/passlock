include config.mk

bin =	cmd/passlist-add cmd/passlist-check cmd/passlist-del \
	cmd/passlist-list

inc =	src/std/arg.h src/std/base64.h src/std/buffer.h src/std/case.h \
	src/std/clock.h src/std/env.h src/std/fmt.h src/std/genalloc.h \
	src/std/int.h src/std/listxt.h src/std/log.h src/std/mem.h \
	src/std/open.h src/std/range.h src/std/stralloc.h src/std/str.h \
	src/std/test.h

obj =	src/std/arg.o src/std/base64.o src/std/buffer.o src/std/case.o \
	src/std/fmt.o src/std/int.o src/std/listxt.o src/std/log.o \
	src/std/mem.o src/std/open.o src/std/range.o src/std/stralloc.o \
	src/std/str.o src/std/test.o

all: ${bin}

${bin}: ${bin:=.o} ${obj} ${inc}
	${CC} ${LFLAGS} -o $@ $@.o ${obj} ${LIB}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

clean:
	rm -f *.a *.o */*.o */*/*.o ${bin} cmd/test

test: ${obj}
	sh tools/test.sh | ${CC} -c ${CFLAGS} -x c -o cmd/test.o -
	${CC} ${CFLAGS} ${LFLAGS} -o cmd/test cmd/test.o ${obj}
	cmd/test

entr:
	find . -name "*.[cht]" | entr make test | grep "[!>]"

install: ${bin}
	mkdir -p ${PREFIX}/bin
	cp ${bin} bin/* ${PREFIX}/bin
	mkdir -p ${PREFIX}/share/man/man1
	cp -f doc/*.1  ${PREFIX}/share/man/man1
	mkdir -p ${PREFIX}/share/man/man8
	cp -f doc/*.8  ${PREFIX}/share/man/man8
