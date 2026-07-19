## review group param_0623  (1 cluster(s), kinds=param)

### proposal for param_0623
struct_name: gatt_find_info_rsp_ctx | is_library: True | library_name: bt att/gatt find-info structures (exact type unresolved) | is_array: None | confidence: low
purpose: ATT Find Information response encoding context (attribute handle / UUID-ish 16-bit fields) used by gatt_find_info_encode.
fields:
  0x8  uint16_t     field_0x8  
  0xe  uint16_t     field_0xe  

<ground-truth bundle for param_0623>
### cluster param_0623  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_find_info_encode @ 0x82772  as param_3  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0623 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint16_t   field_0x8;   /* +0x8  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0xa[0x4];   /* +0xa pad */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=r types=undefined2 */
};
```
