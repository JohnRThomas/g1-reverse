### struct svc_attr_memory_pool  (G1-original)  cid=param_0528

purpose: GATT service attribute memory pool released by svc_attr_memory_release: a size/count word and a pair of allocation pointers near the end.

This object is accessed by these functions (read their fully-named source):
  - svc_attr_memory_release  (as param_1)  ->  recon/readable_sources/app/g1/svc_attr_memory_release.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct svc_attr_memory_pool {
    uint32_t     size_or_count;  /* +0x134  rw=w sz=4 */
    void*        alloc_ptr_1;  /* +0x150  rw=rw sz=4 */
    void*        alloc_ptr_2;  /* +0x154  rw=rw sz=4 */
    uint32_t     field_0x158;  /* +0x158  rw=w sz=4 */   <-- NAME ME
};
```