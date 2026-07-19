## review group param_0010  (1 cluster(s), kinds=param)

### proposal for param_0010
struct_name: array_span32 | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Small array/length descriptor passed into numeric array-scan helper (array_max_skip_nan_b) giving length/count used for indexing.
fields:
  0x4  uint32_t     length  read as index (idx4)
  0x8  uint32_t     count  read as index (idx4)

<ground-truth bundle for param_0010>
### cluster param_0010  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - array_max_skip_nan_b @ 0xe9b4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0010 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
