### struct metal_io_region  (library:metal_io_region)  cid=param_0402

purpose: libmetal/OpenAMP I/O region descriptor used by rpmsg_virtqueue_channel_init and metal_io_block_set.

This object is accessed by these functions (read their fully-named source):
  - rpmsg_virtqueue_channel_init  (as param_4)  ->  recon/readable_sources/app/library/rpmsg_virtqueue_channel_init.c
  - metal_io_block_set  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct metal_io_region {
    void*        virt_or_ops;  /* +0x0  rw=r sz=4 */
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x28;  /* +0x28  rw=r sz=4 */   <-- NAME ME
};
```