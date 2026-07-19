### struct virtqueue  (library:struct virtqueue)  cid=param_0699

purpose: OpenAMP/virtio virtqueue object built by virtqueue_create (param_7): queue index/device ptr plus a run of ring/descriptor-table configuration words.

This object is accessed by these functions (read their fully-named source):
  - virtqueue_create  (as param_7)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct virtqueue {
    uint16_t     vq_queue_index;  /* +0x2  rw=w sz=2 */
    uint32_t     vq_dev_ptr;  /* +0x4  rw=r sz=4 */
    uint16_t     vq_nentries;  /* +0x9  rw=w sz=2 */
    uint16_t     field_0xa;  /* +0xa  rw=w sz=2 */   <-- NAME ME
    uint32_t     vq_ring_desc;  /* +0xc  rw=r sz=4 */
    uint32_t     vq_ring_avail;  /* +0x10  rw=r sz=4 */
    uint32_t     vq_ring_used;  /* +0x14  rw=r sz=4 */
    uint32_t     vq_free_head;  /* +0x18  rw=r sz=4 */
    uint32_t     vq_num_free;  /* +0x1c  rw=r sz=4 */
    uint32_t     vq_callback;  /* +0x20  rw=r sz=4 */
};
```