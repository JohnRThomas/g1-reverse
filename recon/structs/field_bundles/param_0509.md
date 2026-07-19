### struct ipc_rpmsg_instance  (library:ipc rpmsg backend instance)  cid=param_0509

purpose: Large IPC/rpmsg backend instance torn down by ipc_rpmsg_deinit; only three trailing bookkeeping words observed (counters/state near struct end).

This object is accessed by these functions (read their fully-named source):
  - ipc_rpmsg_deinit  (as param_1)  ->  recon/readable_sources/app/library/ipc_rpmsg_deinit.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ipc_rpmsg_instance {
    uint32_t     field_0x19c;  /* +0x19c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x1a0;  /* +0x1a0  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x1a4;  /* +0x1a4  rw=w sz=4 */   <-- NAME ME
};
```