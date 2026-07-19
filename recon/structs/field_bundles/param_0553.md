### struct smp_hdr  (library:smp_hdr (mcumgr))  cid=param_0553

purpose: Mcumgr SMP header built by smp_make_rsp_hdr (op/flags/len/group/seq/id packed).

This object is accessed by these functions (read their fully-named source):
  - smp_make_rsp_hdr  (as param_2)  ->  recon/readable_sources/app/library/smp_make_rsp_hdr.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct smp_hdr {
    uint16_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x2;  /* +0x2  rw=w sz=2 */   <-- NAME ME
    uint16_t     field_0x4;  /* +0x4  rw=rw sz=2,4 */   <-- NAME ME
    uint16_t     field_0x6;  /* +0x6  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```