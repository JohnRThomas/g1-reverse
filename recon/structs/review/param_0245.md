## review group param_0245  (1 cluster(s), kinds=param)

### proposal for param_0245
struct_name: bt_gatt_ccc_store_ctx | is_library: True | library_name: bt_gatt_ccc_cfg | is_array: False | confidence: low
purpose: Object passed to gatt_ccc_write_store_cb during CCC (client characteristic config) settings persistence, carrying a value and flags word
fields:
  0x8  int32_t      ccc_value  
  0xc  uint32_t     ccc_flags  

<ground-truth bundle for param_0245>
### cluster param_0245  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_ccc_write_store_cb @ 0x59dec  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0245 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
};
```
