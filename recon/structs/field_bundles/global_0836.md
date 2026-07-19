### struct uid_enqueue_state  (G1-original)  cid=global_0836

purpose: G1-original global state read by enqueue_uid; a counter/id word at +0x10 and a secondary index/checksum word at +0x24.

This object is accessed by these functions (read their fully-named source):
  - enqueue_uid  (as 0x00018ed8)  ->  recon/readable_sources/app/g1/enqueue_uid.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct uid_enqueue_state {
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
};
```