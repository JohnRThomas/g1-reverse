## review group param_0004  (1 cluster(s), kinds=param)

### proposal for param_0004
struct_name: curve_table_201pt | is_library: False | library_name:  | is_array: True | confidence: high
purpose: 201-point interpolation curve table (backing storage size 0x324 = 201*4 bytes) consumed by curve_table_interp_201pt.
fields:
  0x4  uint32_t     points[0]  first sampled curve value; array continues to +0x320
  0x320  uint32_t     points[200]  last (201st) sampled curve value

<ground-truth bundle for param_0004>
### cluster param_0004  (param, 1 members, 2 fields, size>=0x324)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - curve_table_interp_201pt @ 0xe3a0  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0004 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x318];   /* +0x8 pad */
    uint32_t   field_0x320;   /* +0x320  sz=4 rw=r types=idx4 */
};
```
