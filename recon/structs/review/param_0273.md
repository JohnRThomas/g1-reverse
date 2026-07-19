## review group param_0273  (1 cluster(s), kinds=param)

### proposal for param_0273
struct_name: bt_conn_id_ctx | is_library: True | library_name: bt_conn | is_array: None | confidence: low
purpose: Zephyr bt_conn subset accessed by bt_keys pool lookup (id/type fields used to match keys)
fields:
  0x1  uint16_t     conn_handle  
  0x6  uint8_t      id  

<ground-truth bundle for param_0273>
### cluster param_0273  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_keys_pool_find_or_alloc @ 0x5e614  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0273 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint16_t   field_0x1;   /* +0x1  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x3[0x3];   /* +0x3 pad */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=r types=byte */
    uint8_t    _pad_0x7[0x1];   /* +0x7 pad */
};
```
