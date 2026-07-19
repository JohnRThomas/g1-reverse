## review group param_0015  (1 cluster(s), kinds=param)

### proposal for param_0015
struct_name: spline_point2d | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: 2D control point (x,y) consumed by a 3-point spline interpolation routine.
fields:
  0x4  int32_t      x  idx4 read
  0x8  int32_t      y  idx4 read

<ground-truth bundle for param_0015>
### cluster param_0015  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - spline_interp_3pt @ 0xeb7c  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0015 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
