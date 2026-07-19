### struct log_process_state  (library:Zephyr logging subsystem static state)  cid=global_1068

purpose: Global logging-subsystem state read by log_process (Zephyr logging backend), tracking message counters/indices.

This object is accessed by these functions (read their fully-named source):
  - log_process  (as 0x0004d590)  ->  recon/readable_sources/app/library/log_process.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct log_process_state {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
};
```