### cluster param_0688  (param, 1 members, 2 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - sllist_find_by_name_ci @ 0x8503c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0688 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=ptr */
    uint8_t    _pad_0xc[0x14];   /* +0xc pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```