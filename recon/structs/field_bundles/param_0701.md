### struct virtqueue  (library:virtqueue)  cid=param_0701

purpose: OpenAMP/virtio virtqueue passed to virtqueue_add_buffer (ring size, descriptor table pointer, free/avail indices).

This object is accessed by these functions (read their fully-named source):
  - virtqueue_add_buffer  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct virtqueue {
    uint16_t     vq_nentries;  /* +0xa  rw=r sz=2 */
    int32_t      field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint16_t     vq_free_head;  /* +0x24  rw=rw sz=2 */
    uint16_t     vq_num_free;  /* +0x26  rw=rw sz=2 */
    void *       desc_table;  /* +0x28  rw=r sz=4 */
    uint16_t     field_0x2c;  /* +0x2c  rw=rw sz=2 */   <-- NAME ME
};
```