### struct rpmsg_virtio_shm_pool  (library:rpmsg_virtio_shm_pool)  cid=param_0401

purpose: OpenAMP rpmsg-virtio shared-memory pool descriptor used by rpmsg_virtqueue_channel_init and rpmsg_virtio_shm_pool_get_buffer.

This object is accessed by these functions (read their fully-named source):
  - rpmsg_virtqueue_channel_init  (as param_5)  ->  recon/readable_sources/app/library/rpmsg_virtqueue_channel_init.c
  - rpmsg_virtio_shm_pool_get_buffer  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct rpmsg_virtio_shm_pool {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```