### struct strtod_bigint_scratch  (library:dtoa/strtod internal scratch)  cid=stack_1425

purpose: Stack local (local_7c) in strtod: big-integer/decimal conversion scratch (exponent/digit accumulator + scratch values).

This object is accessed by these functions (read their fully-named source):
  - strtod  (as local_7c)  ->  recon/readable_sources/app/g1/strtod.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct strtod_bigint_scratch {
    int32_t      field_0xc;  /* +0xc  rw=rw sz=4 */   <-- NAME ME
    int32_t      field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
};
```