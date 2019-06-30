libfd/fd_chdir.o:              libfd/fd_chdir.c               include/fd.h
libfd/fd_chmod.o:              libfd/fd_chmod.c               include/fd.h
libfd/fd_chown.o:              libfd/fd_chown.c               include/fd.h
libfd/fd_close.o:              libfd/fd_close.c               include/fd.h
libfd/fd_copy.o:               libfd/fd_copy.c                include/fd.h
libfd/fd_dump.o:               libfd/fd_dump.c                include/fd.h
libfd/fd_move.o:               libfd/fd_move.c                include/fd.h
libfd/fd_read.o:               libfd/fd_read.c                include/fd.h
libfd/fd_recv.o:               libfd/fd_recv.c                include/fd.h
libfd/fd_send.o:               libfd/fd_send.c                include/fd.h
libfd/fd_write.o:              libfd/fd_write.c               include/fd.h

libfd = libfd/fd_chdir.o libfd/fd_chmod.o libfd/fd_chown.o libfd/fd_close.o libfd/fd_copy.o libfd/fd_dump.o libfd/fd_move.o libfd/fd_read.o libfd/fd_recv.o libfd/fd_send.o libfd/fd_write.o
libfd.a: ${libfd}
	rm -f ${@}
	${AR} rc ${@} ${libfd}
	ranlib ${@}
