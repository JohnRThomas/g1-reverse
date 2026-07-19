### struct k_msgq  (library:k_msgq)  cid=param_0726

purpose: Zephyr message queue cleaned up by k_msgq_cleanup.

This object is accessed by these functions (read their fully-named source):
  - k_msgq_cleanup  (as param_1)  ->  recon/readable_sources/app/library/k_msgq_cleanup.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct k_msgq {
    uint8_t      field_0xc;  /* +0xc  rw=rw sz=1 */   <-- NAME ME
    char *       buffer_end;  /* +0x14  rw=r sz=4 */
};
```