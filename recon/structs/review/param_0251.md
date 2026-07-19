## review group param_0251  (1 cluster(s), kinds=param)

### proposal for param_0251
struct_name: gatt_attr_ref | is_library: True | library_name: bt_gatt_attr (subset) | is_array: False | confidence: low
purpose: GATT attribute-like record with a handle/id and a linked pointer, read by gatt_remove_peer_from_attr while scanning peer records.
fields:
  0x8  uint32_t     attr_handle  handle or id
  0xc  void*        next_or_user_data  pointer, next record or user_data

<ground-truth bundle for param_0251>
### cluster param_0251  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_remove_peer_from_attr @ 0x5a3c4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0251 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    void *     field_0xc;   /* +0xc  sz=4 rw=r types=ptr */
};
```
