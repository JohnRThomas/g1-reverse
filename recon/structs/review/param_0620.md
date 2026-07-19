## review group param_0620  (1 cluster(s), kinds=param)

### proposal for param_0620
struct_name: hash_algo_desc | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Small descriptor (function pointer + context) passed to gen_hash_m
fields:
  0x0  void*        hash_fn  r, code pointer
  0x4  uint32_t     ctx_idx  r, idx4

<ground-truth bundle for param_0620>
### cluster param_0620  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - gen_hash_m @ 0x8260c  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0620 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=code */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
