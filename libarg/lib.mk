libarg/arg_0.o:                libarg/arg_0.c                 include/arg.h

libarg = libarg/arg_0.o
libarg.a: ${libarg}
	rm -f ${@}
	${AR} rc ${@} ${libarg}
	ranlib ${@}
