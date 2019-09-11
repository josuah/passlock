VERSION = 0.3
W = -Wall -Wextra -std=c99 --pedantic -Wno-unused-parameter
CFLAGS = $W -g -I'src' -DVERSION='"${VERSION}"' -D_DEFAULT_SOURCE
LFLAGS = $W -static
LIB = -lsodium -lpthread
