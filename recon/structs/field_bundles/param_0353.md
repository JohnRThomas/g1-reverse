### struct twim_xfer_desc  (G1-original)  cid=param_0353

purpose: param_2 of nrfx_twim_xfer - a TWI(M) transfer descriptor (buffer/length words).

This object is accessed by these functions (read their fully-named source):
  - nrfx_twim_xfer  (as param_2)  ->  recon/readable_sources/app/library/nrfx_twim_xfer.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct twim_xfer_desc {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```