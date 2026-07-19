### struct cbprintf_package_hdr  (library:cbprintf package header (Zephyr sys/cbprintf))  cid=param_0128

purpose: cbprintf/log message package descriptor: three consecutive index words describing a formatted-argument package, shared by cbprintf_package_convert, z_log_msg_runtime_create, and arm_fault_forward_handler.

This object is accessed by these functions (read their fully-named source):
  - cbprintf_package_convert  (as param_1)  ->  recon/readable_sources/app/g1/cbprintf_package_convert.c
  - z_log_msg_runtime_create  (as param_3)  ->  recon/readable_sources/app/library/z_log_msg_runtime_create.c
  - arm_fault_forward_handler  (as param_3)  ->  recon/readable_sources/app/library/arm_fault_forward_handler.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct cbprintf_package_hdr {
    uint32_t     len_or_flags;  /* +0x4  rw=r sz=4 */
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```