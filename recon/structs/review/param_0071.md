## review group param_0071  (1 cluster(s), kinds=param)

### proposal for param_0071
struct_name: orientation_state | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Orientation/IMU-fusion state object queried by orientation_get_yaw_deg: a status/valid byte followed by the computed yaw angle in degrees
fields:
  0x28  uint8_t      status  read-only char
  0x2c  float        yaw_deg  read-only float

<ground-truth bundle for param_0071>
### cluster param_0071  (param, 1 members, 2 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - orientation_get_yaw_deg @ 0x267e8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0071 {
    uint8_t    _pad_0x0[0x28];   /* +0x0 pad */
    uint8_t    field_0x28;   /* +0x28  sz=1 rw=r types=char */
    uint8_t    _pad_0x29[0x3];   /* +0x29 pad */
    float      field_0x2c;   /* +0x2c  sz=4 rw=r types=float */
};
```
