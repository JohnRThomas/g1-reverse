### cluster param_0618  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_ccc_changed @ 0x825c0  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0618 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint16_t   field_0x8;   /* +0x8  sz=2 rw=r types=short */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=rw types=short */
    void *     field_0xc;   /* +0xc  sz=4 rw=r types=ptr */
};
```