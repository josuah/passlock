include config.mk
include content.mk

all: ${bin}

${bin}: ${bin:=.o} ${src:.c=.o} ${inc}
	${CC} ${LFLAGS} -o $@ $@.o ${src:.c=.o} ${LIBS}

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
	cp -f doc/*.1  ${PREFIX}/share/man/man1
