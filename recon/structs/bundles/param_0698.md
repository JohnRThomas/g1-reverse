### cluster param_0698  (param, 1 members, 5 fields, size>=0x34)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_000855e6 @ 0x855e6  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0698 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=uint */
    uint8_t    _pad_0x14[0x1c];   /* +0x14 pad */
    void *     field_0x30;   /* +0x30  sz=4 rw=r types=ptr */
};
```