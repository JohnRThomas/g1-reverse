### struct dtoa_r_locals  (G1-original)  cid=stack_0792

purpose: Stack-local scratch in dtoa_r holding intermediate double-to-ASCII conversion words (newlib).

This object is accessed by these functions (read their fully-named source):
  - dtoa_r  (as local_2c)  ->  recon/readable_sources/app/g1/dtoa_r.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct dtoa_r_locals {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```