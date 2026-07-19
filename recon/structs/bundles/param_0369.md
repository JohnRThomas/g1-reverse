### cluster param_0369  (param, 1 members, 3 fields, size>=0x4a8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_load_s24_3le @ 0x68d2c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0369 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x494];   /* +0xc pad */
    uint32_t   field_0x4a0;   /* +0x4a0  sz=4 rw=r types=int */
    void *     field_0x4a4;   /* +0x4a4  sz=4 rw=r types=ptr */
};
```