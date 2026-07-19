## review group param_0002  (1 cluster(s), kinds=param)

### proposal for param_0002
struct_name: batt_soc_curve_ctx | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Battery state-of-charge curve estimation context (coefficients/points for interpolation)
fields:
  0x4  int32_t      soc_curve_x0  
  0x8  int32_t      soc_curve_x1  
  0xc  int32_t      soc_curve_x2  

<ground-truth bundle for param_0002>
### cluster param_0002  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - batt_soc_curve_estimate @ 0xe2b4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0002 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
