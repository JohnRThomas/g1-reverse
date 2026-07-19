## review group param_0322  (1 cluster(s), kinds=param)

### proposal for param_0322
struct_name: cJSON | is_library: True | library_name: cJSON | is_array: None | confidence: medium
purpose: cJSON item node used by cjson_add_item_to_object and traversed via sllist_insert_after
fields:
  0x4  void*        next_or_prev  idx4, likely linked-list pointer
  0xc  uint32_t     type  rw int/uint
  0x20  uint32_t     valueint_or_flags  rw int

<ground-truth bundle for param_0322>
### cluster param_0322  (param, 2 members, 3 fields, size>=0x24)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: cjson; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - cjson_add_item_to_object @ 0x6466c  as param_3  [APPLICATION]
  - sllist_insert_after @ 0x84f2e  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0322 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x4];   /* +0x8 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=int,uint */
    uint8_t    _pad_0x10[0x10];   /* +0x10 pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=int */
};
```
