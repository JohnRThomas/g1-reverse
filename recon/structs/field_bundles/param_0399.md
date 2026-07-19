### struct rpmsg_vqueue_channel_cfg  (G1-original)  cid=param_0399

purpose: Configuration (param_2) passed to rpmsg_virtqueue_channel_init: descriptor count/align words at 0x10/0x14, a count/int at 0x24, and a vring/callback pointer at 0x2c.

This object is accessed by these functions (read their fully-named source):
  - rpmsg_virtqueue_channel_init  (as param_2)  ->  recon/readable_sources/app/library/rpmsg_virtqueue_channel_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct rpmsg_vqueue_channel_cfg {
    uint32_t     field_0x10;  /* +0x10  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=w sz=4 */   <-- NAME ME
    int32_t      field_0x24;  /* +0x24  rw=w sz=4 */   <-- NAME ME
    void *       vring_or_cb;  /* +0x2c  rw=r sz=4 */
};
```