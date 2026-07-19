## review group param_0073  (1 cluster(s), kinds=param)

### proposal for param_0073
struct_name: orientation_state | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: Orientation/IMU state struct providing a computed heading angle used by orientation_get_heading_deg.
fields:
  0x28  uint8_t      field_0x28  status/flag byte
  0x34  float        heading_deg  float, read by orientation_get_heading_deg

<ground-truth bundle for param_0073>
### cluster param_0073  (param, 1 members, 2 fields, size>=0x38)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - orientation_get_heading_deg @ 0x26828  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0073 {
    uint8_t    _pad_0x0[0x28];   /* +0x0 pad */
    uint8_t    field_0x28;   /* +0x28  sz=1 rw=r types=char */
    uint8_t    _pad_0x29[0xb];   /* +0x29 pad */
    float      field_0x34;   /* +0x34  sz=4 rw=r types=float */
};
```
