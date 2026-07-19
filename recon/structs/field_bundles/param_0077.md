### struct system_suspend_ctx  (G1-original)  cid=param_0077

purpose: G1-original large system state/context object referenced by global_system_suspend during power-suspend: a subsystem/callback pointer and a trailing status byte.

This object is accessed by these functions (read their fully-named source):
  - global_system_suspend  (as param_1)  ->  recon/readable_sources/app/g1/global_system_suspend.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct system_suspend_ctx {
    void *       field_0xb70;  /* +0xb70  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0xfe6;  /* +0xfe6  rw=rw sz=1 */   <-- NAME ME
};
```