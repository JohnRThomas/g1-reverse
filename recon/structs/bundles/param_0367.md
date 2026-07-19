### cluster param_0367  (param, 1 members, 10 fields, size>=0x38)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_flush_bits @ 0x685f4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0367 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=rw types=uint */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=int,uint,undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=int,undefined4 */
    uint8_t    _pad_0x18[0x4];   /* +0x18 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=rw types=uint,undefined4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=int */
    uint8_t    _pad_0x24[0x8];   /* +0x24 pad */
    void *     field_0x2c;   /* +0x2c  sz=4 rw=r types=ptr */
    void *     field_0x30;   /* +0x30  sz=4 rw=rw types=ptr */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=rw types=int */
};
```