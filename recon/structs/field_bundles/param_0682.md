### struct watchdog_disable_work_ctx  (G1-original)  cid=param_0682

purpose: Watchdog-disable work context passed to watchdog_disable_write_work: a device/callback pointer at 0x4 and a second pointer at 0x10.

This object is accessed by these functions (read their fully-named source):
  - watchdog_disable_write_work  (as param_1)  ->  recon/readable_sources/app/g1/watchdog_disable_write_work.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct watchdog_disable_work_ctx {
    void *       field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    void *       field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```