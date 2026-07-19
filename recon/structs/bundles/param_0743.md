### cluster param_0743  (param, 1 members, 3 fields, size>=0x58)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_sub_resolve_handle @ 0x86f92  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0743 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint16_t   field_0xc;   /* +0xc  sz=2 rw=rw types=ushort */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=short */
    uint8_t    _pad_0x10[0x44];   /* +0x10 pad */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=w types=int */
};
```