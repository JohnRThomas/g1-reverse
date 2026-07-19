### struct ancs_enqueue_state  (G1-original)  cid=global_0832

purpose: Global ANCS notification-enqueue state (0x18c30) read by enqueue_ancs; sparse queue-cursor words observed.

This object is accessed by these functions (read their fully-named source):
  - enqueue_ancs  (as 0x00018c30)  ->  recon/readable_sources/app/g1/enqueue_ancs.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ancs_enqueue_state {
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
};
```