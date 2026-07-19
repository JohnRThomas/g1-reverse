## review group param_0003  (1 cluster(s), kinds=param)

### proposal for param_0003
struct_name: battery_soc_curve_point | is_library: False | library_name:  | is_array: True | confidence: medium
purpose: One (voltage, soc) point pair read by battery_soc_from_curve when interpolating the state-of-charge curve.
fields:
  0x4  uint32_t     x_value  
  0x8  uint32_t     y_value  

<ground-truth bundle for param_0003>
### cluster param_0003  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - battery_soc_from_curve @ 0xe340  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0003 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
