## review group param_0483  (1 cluster(s), kinds=param)

### proposal for param_0483
struct_name: quaternion_euler_ctx | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: IMU orientation math object: quaternion input floats and output euler-angle/status fields written by quaternion_to_euler
fields:
  0xc  float        quat_w  
  0x10  float        quat_x  
  0x14  float        quat_y  
  0x18  float        quat_z  
  0x28  uint8_t      euler_valid_flag  
  0x2c  float        euler_roll  
  0x30  float        euler_pitch  
  0x34  float        euler_yaw  

<ground-truth bundle for param_0483>
### cluster param_0483  (param, 1 members, 8 fields, size>=0x38)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - quaternion_to_euler @ 0x7cab4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0483 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    float      field_0xc;   /* +0xc  sz=4 rw=r types=float */
    float      field_0x10;   /* +0x10  sz=4 rw=r types=float */
    float      field_0x14;   /* +0x14  sz=4 rw=r types=float */
    float      field_0x18;   /* +0x18  sz=4 rw=r types=float */
    uint8_t    _pad_0x1c[0xc];   /* +0x1c pad */
    uint8_t    field_0x28;   /* +0x28  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x29[0x3];   /* +0x29 pad */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=w types=undefined4 */
};
```
