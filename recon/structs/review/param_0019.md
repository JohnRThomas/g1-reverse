## review group param_0019  (1 cluster(s), kinds=param)

### proposal for param_0019
struct_name: imu_fusion_shared_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Large shared object touched by both panel_level_calc_cached and imu_fusion_thread — IMU/orientation fusion runtime state feeding panel-level (tilt) calculation
fields:
  0x8  uint32_t     state_flags  rw
  0xc  uint32_t     mode  rw
  0x1c  uint32_t     sample_count  r
  0x40  uint32_t     cal_idx_0  r, idx4
  0x44  uint32_t     cal_idx_1  r, idx4
  0x50  uint32_t     cal_idx_2  r, idx4
  0x54  uint32_t     cal_idx_3  r, idx4
  0x80  int32_t      accel_x  r
  0x84  int32_t      accel_y  r
  0x88  int32_t      accel_z  r
  0x178  uint16_t     seq_id  r
  0x198  int32_t      out_x  w, fused output component
  0x19c  int32_t      out_y  w
  0x1a0  int32_t      out_z  w
  0x408  uint32_t     table_idx_a  r, idx4
  0x418  uint32_t     table_idx_b  r, idx4
  0x6ac  uint32_t     table_idx_c  r, idx4

<ground-truth bundle for param_0019>
### cluster param_0019  (param, 2 members, 17 fields, size>=0x6b0)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - panel_level_calc_cached @ 0x25ecc  as param_1  [APPLICATION]
  - imu_fusion_thread @ 0xfe88  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0019 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=int */
    uint8_t    _pad_0x10[0xc];   /* +0x10 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=int */
    uint8_t    _pad_0x20[0x20];   /* +0x20 pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x48[0x8];   /* +0x48 pad */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=r types=idx4 */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x58[0x28];   /* +0x58 pad */
    uint32_t   field_0x80;   /* +0x80  sz=4 rw=r types=int */
    uint32_t   field_0x84;   /* +0x84  sz=4 rw=r types=int */
    uint32_t   field_0x88;   /* +0x88  sz=4 rw=r types=int */
    uint8_t    _pad_0x8c[0xec];   /* +0x8c pad */
    uint16_t   field_0x178;   /* +0x178  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x17a[0x1e];   /* +0x17a pad */
    uint32_t   field_0x198;   /* +0x198  sz=4 rw=w types=int */
    uint32_t   field_0x19c;   /* +0x19c  sz=4 rw=w types=int */
    uint32_t   field_0x1a0;   /* +0x1a0  sz=4 rw=w types=int */
    uint8_t    _pad_0x1a4[0x264];   /* +0x1a4 pad */
    uint32_t   field_0x408;   /* +0x408  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x40c[0xc];   /* +0x40c pad */
    uint32_t   field_0x418;   /* +0x418  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x41c[0x290];   /* +0x41c pad */
    uint32_t   field_0x6ac;   /* +0x6ac  sz=4 rw=r types=idx4 */
};
```
