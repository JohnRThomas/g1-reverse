## review group param_0069  (1 cluster(s), kinds=param)

### proposal for param_0069
struct_name: imu_ahrs_quaternion | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Output quaternion (q0..q3) written/read by the Mahony AHRS filter update.
fields:
  0xc  float        q0  
  0x10  float        q1  
  0x14  float        q2  
  0x18  float        q3  

<ground-truth bundle for param_0069>
### cluster param_0069  (param, 1 members, 4 fields, size>=0x1c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - imu_mahony_ahrs_update @ 0x26624  as param_8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0069 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    float      field_0xc;   /* +0xc  sz=4 rw=r types=float */
    float      field_0x10;   /* +0x10  sz=4 rw=r types=float */
    float      field_0x14;   /* +0x14  sz=4 rw=r types=float */
    float      field_0x18;   /* +0x18  sz=4 rw=r types=float */
};
```
