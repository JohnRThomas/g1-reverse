## review group param_0259  (1 cluster(s), kinds=param)

### proposal for param_0259
struct_name: bt_gatt_notify_params | is_library: True | library_name: bt_gatt_notify_params | is_array: None | confidence: medium
purpose: Zephyr Bluetooth GATT notify parameters struct used by gatt_notify/bt_gatt_notify_cb
fields:
  0x4  void*        attr  r, attribute pointer
  0x8  void*        data  r, notify payload pointer
  0xc  uint16_t     len  r
  0x10  void*        func  r, completion callback
  0x14  void*        user_data  r

<ground-truth bundle for param_0259>
### cluster param_0259  (param, 2 members, 5 fields, size>=0x18)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,gatt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - gatt_notify @ 0x5b680  as param_3  [APPLICATION]
  - bt_gatt_notify_cb @ 0x5b754  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0259 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=undefined4 */
    uint16_t   field_0xc;   /* +0xc  sz=2 rw=r types=undefined2,ushort */
    uint8_t    _pad_0xe[0x2];   /* +0xe pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=undefined4 */
};
```
