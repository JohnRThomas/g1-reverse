## review group param_0016  (1 cluster(s), kinds=param)

### proposal for param_0016
struct_name: spline_3pt_points | is_library: False | library_name:  | is_array: True | confidence: medium
purpose: Array of control-point values fed to spline_interp_3pt for 3-point spline interpolation.
fields:
  0x4  int32_t      point_b  second control point/value, read as idx4
  0x8  int32_t      point_c  third control point/value, read as idx4

<ground-truth bundle for param_0016>
### cluster param_0016  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - spline_interp_3pt @ 0xeb7c  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0016 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
