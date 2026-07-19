## review group param_0274  (1 cluster(s), kinds=param)

### proposal for param_0274
struct_name: bt_keys_irk_lookup_ctx | is_library: True | library_name: struct bt_keys (partial) | is_array: None | confidence: low
purpose: Object passed to bt_keys_find_irk while searching bonded-key records for an IRK match.
fields:
  0x1  uint32_t     field_0x1  
  0x5  uint16_t     field_0x5  
  0x18  uint32_t     field_0x18  

<ground-truth bundle for param_0274>
### cluster param_0274  (param, 1 members, 3 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_keys_find_irk @ 0x5e83c  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0274 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint32_t   field_0x1;   /* +0x1  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x5;   /* +0x5  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x7[0x11];   /* +0x7 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
};
```
