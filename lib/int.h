#ifndef INT_H
#define INT_H

#include <stddef.h>
#include <stdint.h>

#define u32_rotr(x, b) (u32)(((x) >> (b)) | ((x) << (32 - (b))))
#define u64_rotr(x, b) (u64)(((x) >> (b)) | ((x) << (64 - (b))))

#define u32_rotl(x, b) (u32)(((x) << (b)) | ((x) >> (32 - (b))))
#define u64_rotl(x, b) (u64)(((x) << (b)) | ((x) >> (64 - (b))))

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t  i8;

// bin/make-h lib/int.c
int     u8_scan_base(u8 *, char, u8);
size_t  u16_scan_base(u16 *, char const *, size_t, u8);
size_t  u32_scan_base(u32 *, char const *, size_t, u8);
size_t  u64_scan_base(u64 *, char const *, size_t, u8);
u16     u16_unpack_be(const unsigned char *);
u16     u16_unpack_le(const unsigned char *);
u32     u32_unpack_be(const unsigned char *);
u32     u32_unpack_le(const unsigned char *);
u64     u64_unpack_be(const unsigned char *);
u64     u64_unpack_le(const unsigned char *);
void    u16_pack_be(unsigned char *, u16);
void    u16_pack_le(unsigned char *, u16);
void    u32_pack_be(unsigned char *, u32);
void    u32_pack_le(unsigned char *, u32);
void    u64_pack_be(unsigned char *, u64);
void    u64_pack_le(unsigned char *, u64);

#endif
