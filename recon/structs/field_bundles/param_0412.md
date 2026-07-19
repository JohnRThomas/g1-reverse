### struct k_thread_waitq_view  (library:k_thread)  cid=param_0412

purpose: param_1 of add_thread_to_wait_queue: Zephyr thread object linked into a wait queue (linkage words + state/priority bytes).

This object is accessed by these functions (read their fully-named source):
  - add_thread_to_wait_queue  (as param_1)  ->  recon/readable_sources/app/g1/add_thread_to_wait_queue.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct k_thread_waitq_view {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0xd;  /* +0xd  rw=rw sz=1 */   <-- NAME ME
    uint8_t      field_0xe;  /* +0xe  rw=r sz=1 */   <-- NAME ME
};
```