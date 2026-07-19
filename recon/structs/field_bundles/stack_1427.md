### struct strtod_locals  (G1-original)  cid=stack_1427

purpose: Stack-local scratch in strtod holding two intermediate parsing words (mantissa/exponent) (newlib).

This object is accessed by these functions (read their fully-named source):
  - strtod  (as local_3c)  ->  recon/readable_sources/app/g1/strtod.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct strtod_locals {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```