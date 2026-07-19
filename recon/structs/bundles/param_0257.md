### cluster param_0257  (param, 2 members, 4 fields, size>=0x1a)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,gatt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - gatt_indicate @ 0x5b270  as param_3  [APPLICATION]
  - bt_gatt_indicate @ 0x5b378  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0257 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,undefined4 */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x14;   /* +0x14  sz=2 rw=r types=undefined2,ushort */
    uint8_t    field_0x16;   /* +0x16  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x17[0x3];   /* +0x17 pad */
};
```