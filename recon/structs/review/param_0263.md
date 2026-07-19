## review group param_0263  (1 cluster(s), kinds=param)

### proposal for param_0263
struct_name: bt_gatt_subscribe_params | is_library: True | library_name: bt_gatt_subscribe_params | is_array: None | confidence: medium
purpose: GATT subscription parameters used by gatt_subscribe_add / bt_gatt_unsubscribe / gatt_mult_notify_dispatch
fields:
  0x8  uint8_t      field_0x8  
  0x9  uint8_t      field_0x9  
  0xd  uint8_t      field_0xd  

<ground-truth bundle for param_0263>
### cluster param_0263  (param, 4 members, 3 fields, size>=0xe)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,gatt; 0/4 members are LIBRARY-class)

members (4 shown of 4):
  - gatt_subscribe_add @ 0x5c3c4  as param_1  [APPLICATION]
  - bt_gatt_unsubscribe @ 0x5c4f0  as param_1  [APPLICATION]
  - gatt_mult_notify_dispatch @ 0x5c5f0  as param_1  [APPLICATION]
  - FUN_00082e62 @ 0x82e62  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0263 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=undefined1 */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=r types=byte */
    uint8_t    _pad_0xa[0x3];   /* +0xa pad */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=r types=char */
};
```
