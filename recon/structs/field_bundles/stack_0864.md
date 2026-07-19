### struct settings_read_stage  (G1-original)  cid=stack_0864

purpose: Stack-local id/value staging pair inside load_sys_setting while reading a setting.

This object is accessed by these functions (read their fully-named source):
  - load_sys_setting  (as local_9c)  ->  recon/readable_sources/app/g1/load_sys_setting.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct settings_read_stage {
    int32_t      field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```