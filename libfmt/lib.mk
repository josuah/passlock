libfmt/fmt_8long.o:            libfmt/fmt_8long.c             include/fmt.h
libfmt/fmt_long.o:             libfmt/fmt_long.c              include/fmt.h
libfmt/fmt_minus.o:            libfmt/fmt_minus.c             include/fmt.h
libfmt/fmt_plusminus.o:        libfmt/fmt_plusminus.c         include/fmt.h
libfmt/fmt_strn.o:             libfmt/fmt_strn.c              include/fmt.h include/str.h
libfmt/fmt_ulong.o:            libfmt/fmt_ulong.c             include/fmt.h
libfmt/fmt_ulong0.o:           libfmt/fmt_ulong0.c            include/fmt.h
libfmt/fmt_utf8.o:             libfmt/fmt_utf8.c              include/fmt.h
libfmt/fmt_xlong.o:            libfmt/fmt_xlong.c             include/fmt.h
libfmt/fmt_xlong0.o:           libfmt/fmt_xlong0.c            include/fmt.h
libfmt/fmt_xmem.o:             libfmt/fmt_xmem.c              include/fmt.h

libfmt = libfmt/fmt_8long.o libfmt/fmt_long.o libfmt/fmt_minus.o libfmt/fmt_plusminus.o libfmt/fmt_strn.o libfmt/fmt_ulong.o libfmt/fmt_ulong0.o libfmt/fmt_utf8.o libfmt/fmt_xlong.o libfmt/fmt_xlong0.o libfmt/fmt_xmem.o
libfmt.a: ${libfmt}
	rm -f ${@}
	${AR} rc ${@} ${libfmt}
	ranlib ${@}
