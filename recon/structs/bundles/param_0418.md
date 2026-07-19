### cluster param_0418  (param, 4 members, 5 fields, size>=0x2c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (4 shown of 4):
  - _fflush_r @ 0x76ad0  as param_1  [APPLICATION]
  - smakebuf_r @ 0x76cec  as param_1  [APPLICATION]
  - _vfprintf_r @ 0x76ed4  as param_1  [APPLICATION]
  - libc_putc_buffered @ 0x86c88  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0418 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=int,ptr */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=int,ptr */
    void *     field_0xc;   /* +0xc  sz=4 rw=r types=int,ptr */
    uint8_t    _pad_0x10[0x8];   /* +0x10 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=int */
    uint8_t    _pad_0x1c[0xc];   /* +0x1c pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=w types=undefined4 */
};
```