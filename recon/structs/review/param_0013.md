## review group param_0013  (1 cluster(s), kinds=param)

### proposal for param_0013
struct_name: spline_interp_pair_out | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: Output struct receiving two interpolated values from spline_interp_pair_2out.
fields:
  0x4  int32_t      out_x  first interpolated output
  0x8  int32_t      out_y  second interpolated output

<ground-truth bundle for param_0013>
### cluster param_0013  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - spline_interp_pair_2out @ 0xea70  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0013 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
