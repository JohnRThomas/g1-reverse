### cluster param_0619  (param, 1 members, 3 fields, size>=0x1a)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_indicate_rsp @ 0x825d4  as param_5  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0619 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=ptr */
    void *     field_0xc;   /* +0xc  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x10[0x6];   /* +0x10 pad */
    uint8_t    field_0x16;   /* +0x16  sz=1 rw=rw types=char */
    uint8_t    _pad_0x17[0x3];   /* +0x17 pad */
};
```