### struct dtoa_scratch  (G1-original)  cid=param_0423

purpose: Third parameter scratch state in dtoa (double-to-ASCII): three index words.

This object is accessed by these functions (read their fully-named source):
  - dtoa  (as param_3)  ->  recon/readable_sources/app/library/dtoa.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct dtoa_scratch {
    int32_t      field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```