## review group param_0255  (1 cluster(s), kinds=param)

### proposal for param_0255
struct_name: bt_gatt_attr | is_library: True | library_name: Zephyr Bluetooth: struct bt_gatt_attr | is_array: None | confidence: high
purpose: Zephyr GATT attribute descriptor read by bt_gatt_attr_get_handle/bt_gatt_attr_value_handle: user_data pointer and 16-bit handle field match the stock layout.
fields:
  0xc  void *       user_data  pointer field, matches bt_gatt_attr.user_data offset
  0x10  uint16_t     handle  matches bt_gatt_attr.handle offset

<ground-truth bundle for param_0255>
### cluster param_0255  (param, 3 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 1/3 members are LIBRARY-class)

members (3 shown of 3):
  - bt_gatt_attr_get_handle @ 0x5a9f4  as param_1  [APPLICATION]
  - bt_gatt_attr_value_handle @ 0x82c0e  as param_1  [LIBRARY]
  - FUN_00082c48 @ 0x82c48  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0255 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    void *     field_0xc;   /* +0xc  sz=4 rw=r types=idx4,ptr */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
};
```
