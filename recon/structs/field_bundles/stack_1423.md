### struct snprintf_locals  (G1-original)  cid=stack_1423

purpose: Stack scratch (two format-state words) inside snprintf.

This object is accessed by these functions (read their fully-named source):
  - snprintf  (as local_80)  ->  recon/readable_sources/app/g1/snprintf.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct snprintf_locals {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```