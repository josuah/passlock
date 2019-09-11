#!/bin/sh -e

f() { sort | tr '\n' ' ' | fold -s -w 70 | sed 's/^/	/; s/ *$/ \\/; $ s/ \\//'; }
c() { find src -name '*.c' | f; }
h() { find src -name '*.h' | f; }
m() { ls doc | sed -rn 's/.*\.([0-9])$/\1/p' | sort -u; }
b() { find cmd -name '*.c' | sed 's/\.c//' | f; }

echo 'include config.mk'
echo ''
echo "bin =$(b)"
echo ''
echo "inc =$(h)"
echo ''
echo "obj =$(c | sed 's/\.c/\.o/g')"
echo ''
echo 'all: ${bin}'
echo ''
echo '${bin}: ${bin:=.o} ${obj} ${inc}'
echo '	${CC} ${LFLAGS} -o $@ $@.o ${obj} ${LIB}'
echo ''
echo '.c.o:'
echo '	${CC} -c ${CFLAGS} -o $@ $<'
echo ''
echo 'clean:'
echo '	rm -f *.a *.o */*.o */*/*.o ${bin} cmd/test'
echo ''
echo 'test: ${obj}'
echo '	sh tools/test.sh | ${CC} -c ${CFLAGS} -x c -o cmd/test.o -'
echo '	${CC} ${CFLAGS} ${LFLAGS} -o cmd/test cmd/test.o ${obj}'
echo '	cmd/test'
echo ''
echo 'entr:'
echo '	find . -name "*.[cht]" | entr make test | grep "[!>]"'
echo ''
echo 'install: ${bin}'
echo '	mkdir -p ${PREFIX}/bin'
echo '	cp ${bin} bin/* ${PREFIX}/bin'
for x in $(m); do
echo "	mkdir -p \${PREFIX}/share/man/man$x"
echo "	cp -f doc/*.$x  \${PREFIX}/share/man/man$x"
done
