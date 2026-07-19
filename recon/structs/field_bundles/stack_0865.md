### struct load_sys_setting_locals  (G1-original)  cid=stack_0865

purpose: Stack-local key/value byte pair in load_sys_setting separated by a 15-byte name/scratch gap.

This object is accessed by these functions (read their fully-named source):
  - load_sys_setting  (as local_87)  ->  recon/readable_sources/app/g1/load_sys_setting.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct load_sys_setting_locals {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x10;  /* +0x10  rw=r sz=1 */   <-- NAME ME
};
```