### struct new_task_locals  (G1-original)  cid=stack_0910

purpose: Stack local (local_2c) in process_for_new_task: two related index/id words.

This object is accessed by these functions (read their fully-named source):
  - process_for_new_task  (as local_2c)  ->  recon/readable_sources/app/g1/process_for_new_task.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct new_task_locals {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```