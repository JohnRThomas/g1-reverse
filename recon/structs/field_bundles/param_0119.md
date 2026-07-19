### struct quicknote_buffer_pool  (G1-original)  cid=param_0119

purpose: Quicknote subsystem buffer-pool descriptor initialized by quicknote_buffer_pool_init: pool metadata (8 leading words) plus a large buffer region and two tail fields.

This object is accessed by these functions (read their fully-named source):
  - quicknote_buffer_pool_init  (as param_1)  ->  recon/readable_sources/app/g1/quicknote_buffer_pool_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct quicknote_buffer_pool {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x344;  /* +0x344  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x350;  /* +0x350  rw=r sz=4 */   <-- NAME ME
};
```