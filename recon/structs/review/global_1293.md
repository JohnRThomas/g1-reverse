## review group global_1293  (1 cluster(s), kinds=global)

### proposal for global_1293
struct_name: cjson_hooks_or_error | is_library: True | library_name: cJSON internal_hooks / global_error | is_array: None | confidence: low
purpose: cJSON internal global state referenced from cjson_parse_with_opts (likely the static global_hooks allocator table or global_error position tracker)
fields:
  0x4  void*        field_0x4  candidate: free_fn or position
  0x8  void*        field_0x8  candidate: realloc_fn

<ground-truth bundle for global_1293>
### cluster global_1293  (global, 1 members, 2 fields, size>=0xc)

Global object at fixed address 0x00064c34.

library hint: LIKELY LIBRARY (prefixes: cjson; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - cjson_parse_with_opts @ 0x64b64  as 0x00064c34  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1293 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
