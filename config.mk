VERSION = 0.6
W = -Wall -Wextra -std=c99 --pedantic
I = -I'${LIBSODIUM}/include' -I'src'
L = -L'${LIBSODIUM}/lib'
D = -D_POSIX_C_SOURCE=200811L -DVERSION='"${VERSION}"'
CFLAGS = $W $I $D -g
LFLAGS = $W $L
LIBS = -static -lsodium -lpthread
