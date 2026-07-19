## review group param_0611  (1 cluster(s), kinds=param)

### proposal for param_0611
struct_name: att_indicate_params | is_library: True | library_name: bt_gatt_indicate_params | is_array: False | confidence: low
purpose: ATT indicate parameters struct passed to att_indicate (BLE attribute protocol), holding a 32-bit value and 16-bit handle.
fields:
  0xc  uint32_t     field_0xc  
  0x10  uint16_t     handle  attribute handle

<ground-truth bundle for param_0611>
### cluster param_0611  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - att_indicate @ 0x821c0  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0611 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
};
```
