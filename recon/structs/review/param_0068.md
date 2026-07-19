## review group param_0068  (1 cluster(s), kinds=param)

### proposal for param_0068
struct_name: imu_fusion_calib_params | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: IMU fusion calibration parameter block consumed by imu_fusion_state_init (bias/scale table)
fields:
  0x4  uint32_t     cal_0  r, idx4
  0x8  uint32_t     cal_1  r, idx4
  0xc  uint32_t     cal_2  r, idx4
  0x10  uint32_t     cal_3  r, idx4
  0x14  uint32_t     cal_4  r, idx4
  0x18  uint32_t     cal_5  r, idx4
  0x1c  uint32_t     cal_6  r, idx4
  0x20  uint32_t     cal_7  r, idx4
  0x24  uint32_t     cal_8  r, idx4
  0x38  uint32_t     cal_9  r, idx4
  0x3c  uint32_t     cal_10  r, idx4

<ground-truth bundle for param_0068>
### cluster param_0068  (param, 1 members, 12 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - imu_fusion_state_init @ 0x265b8  as param_1  [APPLICATION]

layout notes: 0x8: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0068 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint16_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    field_0xa;   /* +0xa  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0xb[0x1];   /* +0xb pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x28[0x10];   /* +0x28 pad */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
};
```
