### struct imu_fusion_calib_params  (G1-original)  cid=param_0068

purpose: IMU fusion calibration parameter block (bias/scale table) consumed by imu_fusion_state_init.

This object is accessed by these functions (read their fully-named source):
  - imu_fusion_state_init  (as param_1)  ->  recon/readable_sources/app/g1/imu_fusion_state_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct imu_fusion_calib_params {
    uint32_t     cal_0;  /* +0x4  rw=r sz=4 */
    uint32_t     cal_1;  /* +0x8  rw=r sz=4 */
    uint8_t      field_0xa;  /* +0xa  rw=w sz=1 */   <-- NAME ME
    uint32_t     cal_2;  /* +0xc  rw=r sz=4 */
    uint32_t     cal_3;  /* +0x10  rw=r sz=4 */
    uint32_t     cal_4;  /* +0x14  rw=r sz=4 */
    uint32_t     cal_5;  /* +0x18  rw=r sz=4 */
    uint32_t     cal_6;  /* +0x1c  rw=r sz=4 */
    uint32_t     cal_7;  /* +0x20  rw=r sz=4 */
    uint32_t     cal_8;  /* +0x24  rw=r sz=4 */
    uint32_t     cal_9;  /* +0x38  rw=r sz=4 */
    uint32_t     cal_10;  /* +0x3c  rw=r sz=4 */
};
```