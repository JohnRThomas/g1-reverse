### struct buffer_pool_freelist  (G1-original)  cid=param_0717

purpose: Buffer-pool freelist descriptor initialized by buffer_pool_freelist_init (head pointer, block size, counts).

This object is accessed by these functions (read their fully-named source):
  - buffer_pool_freelist_init  (as param_1)  ->  recon/readable_sources/app/g1/buffer_pool_freelist_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct buffer_pool_freelist {
    void *       free_head;  /* +0x0  rw=r sz=4 */
    uint16_t     block_size;  /* +0x4  rw=w sz=2 */
    uint32_t     block_count;  /* +0x8  rw=r sz=4 */
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
};
```