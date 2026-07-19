### struct arm_mpu_configure_locals  (G1-original)  cid=stack_1112

purpose: Stack-local MPU region-config temporaries (local_38) in arm_core_mpu_configure.

This object is accessed by these functions (read their fully-named source):
  - arm_core_mpu_configure  (as local_38)  ->  recon/readable_sources/app/library/arm_core_mpu_configure.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct arm_mpu_configure_locals {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```