### cluster param_0373  (param, 1 members, 5 fields, size>=0x4ac)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_encode @ 0x69238  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0373 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x494];   /* +0xc pad */
    uint32_t   field_0x4a0;   /* +0x4a0  sz=4 rw=r types=int */
    uint32_t   field_0x4a4;   /* +0x4a4  sz=4 rw=r types=int */
    uint32_t   field_0x4a8;   /* +0x4a8  sz=4 rw=r types=int */
};
```