## review group param_0241  (1 cluster(s), kinds=param)

### proposal for param_0241
struct_name: bt_att_find_type_req | is_library: True | library_name: bt_att_find_type_req | is_array: None | confidence: medium
purpose: Zephyr ATT 'Find Type Value Request' PDU structure parsed by att_find_type_req.
fields:
  0xc  uint32_t     field_0xc  attribute type/UUID field
  0x10  uint8_t      field_0x10  flag/attribute group byte

<ground-truth bundle for param_0241>
### cluster param_0241  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - att_find_type_req @ 0x59550  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0241 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0x11[0x3];   /* +0x11 pad */
};
```
