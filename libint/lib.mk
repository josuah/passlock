libint/u16_pack_be.o:          libint/u16_pack_be.c           include/int.h
libint/u16_pack_le.o:          libint/u16_pack_le.c           include/int.h
libint/u16_scan_base.o:        libint/u16_scan_base.c         include/int.h
libint/u16_unpack_be.o:        libint/u16_unpack_be.c         include/int.h
libint/u16_unpack_le.o:        libint/u16_unpack_le.c         include/int.h
libint/u32_pack_be.o:          libint/u32_pack_be.c           include/int.h
libint/u32_pack_le.o:          libint/u32_pack_le.c           include/int.h
libint/u32_scan_base.o:        libint/u32_scan_base.c         include/int.h
libint/u32_unpack_be.o:        libint/u32_unpack_be.c         include/int.h
libint/u32_unpack_le.o:        libint/u32_unpack_le.c         include/int.h
libint/u64_pack_be.o:          libint/u64_pack_be.c           include/int.h
libint/u64_pack_le.o:          libint/u64_pack_le.c           include/int.h
libint/u64_scan_base.o:        libint/u64_scan_base.c         include/int.h
libint/u64_unpack_be.o:        libint/u64_unpack_be.c         include/int.h
libint/u64_unpack_le.o:        libint/u64_unpack_le.c         include/int.h
libint/u8_scan_base.o:         libint/u8_scan_base.c          include/int.h

libint = libint/u16_pack_be.o libint/u16_pack_le.o libint/u16_scan_base.o libint/u16_unpack_be.o libint/u16_unpack_le.o libint/u32_pack_be.o libint/u32_pack_le.o libint/u32_scan_base.o libint/u32_unpack_be.o libint/u32_unpack_le.o libint/u64_pack_be.o libint/u64_pack_le.o libint/u64_scan_base.o libint/u64_unpack_be.o libint/u64_unpack_le.o libint/u8_scan_base.o
libint.a: ${libint}
	rm -f ${@}
	${AR} rc ${@} ${libint}
	ranlib ${@}
