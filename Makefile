include config.mk

bin = passlist-add passlist-check passlist-del passlist-list
inc = src/listxt.h src/log.h src/tool.h
src = src/listxt.c src/log.c src/tool.c
obj = ${src:.c=.o}

all: ${bin}

${bin}: ${bin:=.o} ${obj} ${inc}
	${CC} ${LFLAGS} -o $@ $@.o ${obj} ${LIB}

.c.o:
	${CC} -c ${CFLAGS} -o $@ $<

clean:
	rm -f *.a *.o */*.o */*/*.o ${bin} cmd/test

release:
	git tag -f "${VERSION}"

install: ${bin}
	mkdir -p ${PREFIX}/bin
	cp ${bin} ${PREFIX}/bin
	mkdir -p ${PREFIX}/share/man/man1
	cp -f *.1  ${PREFIX}/share/man/man1
	mkdir -p ${PREFIX}/share/man/man8
	cp -f *.8  ${PREFIX}/share/man/man8
