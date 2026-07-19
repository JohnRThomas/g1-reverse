### cluster param_0250  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_cf_cfg_clear @ 0x5a39c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0250 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x9[0x3];   /* +0x9 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=w types=undefined4 */
};
```