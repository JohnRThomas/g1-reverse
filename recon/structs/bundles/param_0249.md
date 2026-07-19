### cluster param_0249  (param, 2 members, 3 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - gatt_write_ccc_rsp @ 0x5a1b0  as param_5  [APPLICATION]
  - list_unlink_and_release @ 0x828e8  as param_4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0249 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=2,4 rw=r types=idx4,short */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0xc];   /* +0xc pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
};
```