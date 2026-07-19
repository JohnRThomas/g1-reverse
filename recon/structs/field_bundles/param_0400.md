### struct rpmsg_vq_alloc_info  (G1-original)  cid=param_0400

purpose: Virtqueue allocation descriptor passed to rpmsg_virtqueue_channel_init (flag/id byte plus a pointer+size pair).

This object is accessed by these functions (read their fully-named source):
  - rpmsg_virtqueue_channel_init  (as param_6)  ->  recon/readable_sources/app/library/rpmsg_virtqueue_channel_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct rpmsg_vq_alloc_info {
    uint8_t      flags_or_id;  /* +0x2  rw=r sz=1 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```