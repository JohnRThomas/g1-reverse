## review group param_0225  (1 cluster(s), kinds=param)

### proposal for param_0225
struct_name: find_type_cb_ctx | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Callback context for find_type_cb: a function pointer plus an associated index/id used during a GATT attribute-type search.
fields:
  0x0  void *       callback_fn  
  0x4  uint32_t     user_index  

<ground-truth bundle for param_0225>
### cluster param_0225  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - find_type_cb @ 0x583d0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0225 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
