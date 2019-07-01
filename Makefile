LIBSODIUM_LIB = ${PREFIX}/lib
LIBSODIUM_INC = ${PREFIX}/include

W = -Wall -Wextra -Wno-unused-parameter
CFLAGS = -g -I'include' -I'${LIBSODIUM_INC}' -static $W
LFLAGS = -L${LIBSODIUM_LIB} -lsodium

bin = passsafe-add passsafe-check passsafe-del passsafe-list

all: ${bin}

clean:
	rm -f *.a *.o */*.o leapsecs leapsecs.dat

install: all
	mkdir -p "${PREFIX}/bin"
	cp ${bin} "${PREFIX}/bin"

.c.o:
	${CC} -c ${CFLAGS} ${include} -o $@ $<

leapsecs.dat: leapsecs leapsecs.txt
	./leapsecs <leapsecs.txt >leapsecs.dat

# bin/make-lib lib*/

include libarg/lib.mk
include libbuffer/lib.mk
include libfd/lib.mk
include libfmt/lib.mk
include libint/lib.mk
include liblistxt/lib.mk
include liblog/lib.mk
include libmem/lib.mk
include libopen/lib.mk
include libstr/lib.mk
include libstralloc/lib.mk

lib = liblistxt.a libopen.a liblog.a libbuffer.a libfd.a libstralloc.a libmem.a libfmt.a libstr.a libint.a libarg.a

# bin/make-bin *.c

inc = include/arg.h include/buffer.h include/env.h include/fd.h include/fmt.h include/genalloc.h include/int.h include/listxt.h include/log.h include/mem.h include/open.h include/str.h include/stralloc.h

bin: passsafe-add passsafe-check passsafe-del passsafe-list

passsafe-add: passsafe-add.o ${lib} ${inc}
	${CC} ${LFLAGS} -o ${@} ${@}.o ${lib}

passsafe-check: passsafe-check.o ${lib} ${inc}
	${CC} ${LFLAGS} -o ${@} ${@}.o ${lib}

passsafe-del: passsafe-del.o ${lib} ${inc}
	${CC} ${LFLAGS} -o ${@} ${@}.o ${lib}

passsafe-list: passsafe-list.o ${lib} ${inc}
	${CC} ${LFLAGS} -o ${@} ${@}.o ${lib}
