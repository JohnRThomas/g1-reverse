## review group param_0228  (1 cluster(s), kinds=param)

### proposal for param_0228
struct_name: bt_att_read_type_data | is_library: True | library_name: struct bt_att_read_type_data (Zephyr BT host, subsys/bluetooth/host/att.c) | is_array: None | confidence: medium
purpose: Zephyr Bluetooth ATT Read-By-Type request iteration context shared by read_group_cb and att_read_type_iter_cb.
fields:
  0x0  uint8_t      field_0x0  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for param_0228>
### cluster param_0228  (param, 2 members, 6 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - read_group_cb @ 0x58750  as param_3  [LIBRARY]
  - att_read_type_iter_cb @ 0x58808  as param_3  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0228 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint8_t    field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=w types=char,undefined1 */
    uint8_t    _pad_0x6[0x2];   /* +0x6 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
