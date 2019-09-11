#!/bin/sh -e

cd src
echo '#include "std/log.h"'
echo '#include "std/test.h"'
find * -name '*.t' | sed -r 's/(.*).t/#include "\1.h"/; p; s/."$/t"/'
echo 'int main(void) {'
echo '	log_init(5);'
echo '	test_init();'
find * -name '*.t' | sed 's/[/]/_/g; s/^/	test_/; s/.t$/();/'
echo '	test_summary();'
echo '	return !test_ok;'
echo '}'
