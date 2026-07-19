### struct record_type8  (G1-original)  cid=param_0051

purpose: Output record filled by fill_record_type8: five leading words written, plus a trailing index read at 0x60.

This object is accessed by these functions (read their fully-named source):
  - fill_record_type8  (as param_1)  ->  recon/readable_sources/app/g1/fill_record_type8.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct record_type8 {
    uint32_t     field_0x4;  /* +0x4  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x60;  /* +0x60  rw=r sz=4 */   <-- NAME ME
};
```