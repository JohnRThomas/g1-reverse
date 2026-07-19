### struct z_kernel_sched_state  (library:_kernel)  cid=global_1405

purpose: Zephyr kernel scheduler global (0x73a64) touched by z_reschedule; ready-queue/cpu-state ints.

This object is accessed by these functions (read their fully-named source):
  - z_reschedule  (as 0x00073a64)  ->  recon/readable_sources/app/library/z_reschedule.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct z_kernel_sched_state {
    int32_t      field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
};
```