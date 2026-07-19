## review group param_0155  (1 cluster(s), kinds=param)

### proposal for param_0155
struct_name: bt_gatt_dm_data | is_library: True | library_name: bt_gatt_dm | is_array: None | confidence: medium
purpose: GATT discovery manager attribute-add context (Zephyr bt_gatt_dm subsystem)
fields:
  0x4  uint16_t     field_0x4  ushort
  0xc  uint32_t     field_0xc  idx4
  0x12  uint16_t     field_0x12  undefined2

<ground-truth bundle for param_0155>
### cluster param_0155  (param, 2 members, 3 fields, size>=0x16)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - gatt_dm_data_add_attribute @ 0x4e9a0  as param_1  [APPLICATION]
  - discovery_callback @ 0x4ea78  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0155 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=r types=undefined2,ushort */
    uint8_t    _pad_0x6[0x6];   /* +0x6 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x2];   /* +0x10 pad */
    uint16_t   field_0x12;   /* +0x12  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x14[0x2];   /* +0x14 pad */
};
```
