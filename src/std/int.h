#ifndef STD_INT_H
#define STD_INT_H

#include <stddef.h>
#include <stdint.h>

/*
 * Adapted from Dan Bernstein (cr.yp.to) code for djbdns (public domain) as
 * well as from Laurent Bercot (skarnet.org) code for skalibs (ISC licence).
 */

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

size_t          u8_fmt(char *, u8);
size_t          u16_fmt(char *, u16);
size_t          u32_fmt(char *, u32);
size_t          u64_fmt(char *, u64);

size_t          i8_fmt(char *, i8);
size_t          i16_fmt(char *, i16);
size_t          i32_fmt(char *, i32);
size_t          i64_fmt(char *, i64);

int             u8_scan_base_char(char, u8 *, u8);
size_t          i64_scan_base(char const *, i64 *, u8);
size_t          u16_scan_base(char const *, u16 *, u8);
size_t          u32_scan_base(char const *, u32 *, u8);
size_t          u64_scan_base(char const *, u64 *, u8);
size_t          u8_scan_base(char const *, u8 *, u8);
u16             u16_unpack_be(const unsigned char *);
u16             u16_unpack_le(const unsigned char *);
u32             u32_unpack_be(const unsigned char *);
u32             u32_unpack_le(const unsigned char *);
u64             u64_unpack_be(const unsigned char *);
u64             u64_unpack_le(const unsigned char *);
void            u16_pack_be(unsigned char *, u16);
void            u16_pack_le(unsigned char *, u16);
void            u32_pack_be(unsigned char *, u32);
void            u32_pack_le(unsigned char *, u32);
void            u64_pack_be(unsigned char *, u64);
void            u64_pack_le(unsigned char *, u64);

#endif
