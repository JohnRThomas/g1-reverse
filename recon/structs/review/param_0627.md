## review group param_0627  (1 cluster(s), kinds=param)

### proposal for param_0627
struct_name: gatt_sc_ctx | is_library: True | library_name: struct gatt_sc_cfg / sc_data (Zephyr BT GATT) | is_array: None | confidence: low
purpose: Zephyr Bluetooth GATT Service Changed context cleared by gatt_sc_ctx_clear.
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for param_0627>
### cluster param_0627  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_sc_ctx_clear @ 0x82928  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0627 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
