### struct reg_dev_ctx  (G1-original)  cid=param_0506

purpose: Register-level device driver context (config word, register-map ptr, far threshold value) shared across dev_write_reg3/4, dev_reg_modify_bits, dev_set_threshold_and_arm.

This object is accessed by these functions (read their fully-named source):
  - FUN_0007eb7e  (as param_1)  [no source file]
  - dev_write_reg3  (as param_1)  ->  recon/readable_sources/app/g1/dev_write_reg3.c
  - dev_write_reg4  (as param_1)  ->  recon/readable_sources/app/g1/dev_write_reg4.c
  - dev_reg_modify_bits  (as param_1)  ->  recon/readable_sources/app/g1/dev_reg_modify_bits.c
  - dev_set_threshold_and_arm  (as param_1)  ->  recon/readable_sources/app/g1/dev_set_threshold_and_arm.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct reg_dev_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    int32_t      threshold;  /* +0xb0  rw=r sz=4 */
};
```