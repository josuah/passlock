VERSION = 0.5
W = -Wall -Wextra -std=c99 --pedantic
CFLAGS = $W -I'/usr/local/include' -g -I'src' -DVERSION='"${VERSION}"'
LFLAGS = $W -L'/usr/local/lib' -static
LIB = -lsodium -lpthread
