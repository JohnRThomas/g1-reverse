## review group param_0009  (1 cluster(s), kinds=param)

### proposal for param_0009
struct_name: array_max_skip_nan_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Pointer parameter to array_max_skip_nan_a; holds two index/length fields describing an array scan (bounds or accumulator state).
fields:
  0x4  uint32_t     field_0x4  index/count
  0x8  uint32_t     field_0x8  index/count

<ground-truth bundle for param_0009>
### cluster param_0009  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - array_max_skip_nan_a @ 0xe954  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0009 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
