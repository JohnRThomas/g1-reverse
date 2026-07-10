#ifndef G1_COMPAT_TYPES_H
#define G1_COMPAT_TYPES_H
/* Maps decompiler/Zephyr short type spellings to standard C types so the
 * reconstructed + symbolized sources compile. Generated for the assembly step. */
#include <stdint.h>
typedef uint8_t   u8;   typedef int8_t   s8;
typedef uint16_t  u16;  typedef int16_t  s16;
typedef uint32_t  u32;  typedef int32_t  s32;
typedef uint64_t  u64;  typedef int64_t  s64;
typedef uint8_t   uchar;    typedef uint8_t  byte;
typedef unsigned int   uint;    typedef unsigned short ushort;   typedef unsigned long ulong;
typedef uint8_t  undefined;  typedef uint8_t undefined1; typedef uint16_t undefined2;
typedef uint32_t undefined4; typedef uint64_t undefined8;
typedef uint32_t uint3;      /* Ghidra 3-byte artifact, widened */
#endif
