### cluster param_0262  (param, 2 members, 5 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,gatt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - gatt_subscribe_add @ 0x5c3c4  as param_2  [APPLICATION]
  - bt_gatt_unsubscribe @ 0x5c4f0  as param_2  [APPLICATION]

layout notes: 0xc: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0262 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=rw types=undefined2,ushort */
    uint8_t    _pad_0x6[0x6];   /* +0x6 pad */
    uint16_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=short */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14[0x4];   /* +0x14 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
};
```