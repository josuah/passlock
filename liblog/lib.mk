liblog/log_die.o:              liblog/log_die.c               include/log.h include/buffer.h
liblog/log_die_sys.o:          liblog/log_die_sys.c           include/log.h include/buffer.h
liblog/log_init.o:             liblog/log_init.c              include/log.h include/env.h include/int.h include/str.h
liblog/log_level.o:            liblog/log_level.c             include/log.h
liblog/log_put.o:              liblog/log_put.c               include/log.h include/buffer.h
liblog/log_put_sys.o:          liblog/log_put_sys.c           include/log.h include/buffer.h
liblog/log_usage.o:            liblog/log_usage.c             include/log.h include/buffer.h

liblog = liblog/log_die.o liblog/log_die_sys.o liblog/log_init.o liblog/log_level.o liblog/log_put.o liblog/log_put_sys.o liblog/log_usage.o
liblog.a: ${liblog}
	rm -f ${@}
	${AR} rc ${@} ${liblog}
	ranlib ${@}
