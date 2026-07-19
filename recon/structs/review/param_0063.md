## review group param_0063  (1 cluster(s), kinds=param)

### proposal for param_0063
struct_name: imu_fusion_ctx | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: IMU sensor-fusion output context registered via register_imu_funsion_context; trailing four write-only words look like a quaternion or 3-axis+scalar output.
fields:
  0x8c  float        quat_w  write-only, likely fusion output component
  0x90  float        quat_x  write-only, likely fusion output component
  0x94  float        quat_y  write-only, likely fusion output component
  0x98  float        quat_z  write-only, likely fusion output component

<ground-truth bundle for param_0063>
### cluster param_0063  (param, 1 members, 4 fields, size>=0x9c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - register_imu_funsion_context @ 0x26250  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0063 {
    uint8_t    _pad_0x0[0x8c];   /* +0x0 pad */
    uint32_t   field_0x8c;   /* +0x8c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x90;   /* +0x90  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x94;   /* +0x94  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x98;   /* +0x98  sz=4 rw=w types=undefined4 */
};
```
