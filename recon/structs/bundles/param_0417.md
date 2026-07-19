### cluster param_0417  (param, 10 members, 17 fields, size>=0x68)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 0/10 members are LIBRARY-class)

members (10 shown of 10):
  - _fflush_r @ 0x76ad0  as param_2  [APPLICATION]
  - smakebuf_r @ 0x76cec  as param_2  [APPLICATION]
  - _vfprintf_r @ 0x76ed4  as param_2  [APPLICATION]
  - stdio_fclose @ 0x77d54  as param_2  [APPLICATION]
  - __sfvwrite_r @ 0x77e70  as param_2  [APPLICATION]
  - printf_parse_format @ 0x78d90  as param_2  [APPLICATION]
  - stdio_flush_write_buffer @ 0x86a0e  as param_2  [APPLICATION]
  - swhatbuf_r @ 0x86b7e  as param_2  [APPLICATION]
  - libc_putc_buffered @ 0x86c88  as param_3  [APPLICATION]
  - iobuf_ensure_capacity_and_append @ 0x87736  as param_2  [APPLICATION]

layout notes: overlap at 0x3 (prev field ends 0x4); overlap at 0xe (prev field ends 0x10)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0417 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=2,4 rw=r types=idx4,short,ushort */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4,int */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1c[0x4];   /* +0x1c pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x24[0x4];   /* +0x24 pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x30[0x4];   /* +0x30 pad */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x38[0x8];   /* +0x38 pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x44[0x10];   /* +0x44 pad */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x5c[0x8];   /* +0x5c pad */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=r types=int */
};
```