### struct rpmsg_virtio_device  (library:rpmsg_virtio_device)  cid=param_0714

purpose: param_1 of rpmsg_deinit_vdev: OpenAMP rpmsg virtio device torn down; two adjacent words at 0xa4/0xa8 (vring/vdev handles).

This object is accessed by these functions (read their fully-named source):
  - rpmsg_deinit_vdev  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct rpmsg_virtio_device {
    uint32_t     field_0xa4;  /* +0xa4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xa8;  /* +0xa8  rw=r sz=4 */   <-- NAME ME
};
```