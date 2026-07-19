## review group param_0597  (1 cluster(s), kinds=param)

### proposal for param_0597
struct_name: bt_l2cap_chan | is_library: True | library_name: struct bt_l2cap_chan | is_array: None | confidence: medium
purpose: Zephyr Bluetooth L2CAP channel context passed to l2cap_chan_disconnected_cb.
fields:
  0x4  uint16_t     field_0x4  
  0x8  void *       field_0x8  
  0xc  uint32_t     field_0xc  

<ground-truth bundle for param_0597>
### cluster param_0597  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: l2cap; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - l2cap_chan_disconnected_cb @ 0x81a76  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0597 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x6[0x2];   /* +0x6 pad */
    void *     field_0x8;   /* +0x8  sz=4 rw=r types=ptr */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
};
```
