### struct ndef_record_scratch  (G1-original)  cid=stack_0897

purpose: Stack scratch buffer in st25dv_build_and_write_ndef_records used to assemble NFC NDEF record fields before writing to the ST25DV tag.

This object is accessed by these functions (read their fully-named source):
  - st25dv_build_and_write_ndef_records  (as local_6c)  ->  recon/readable_sources/app/g1/st25dv_build_and_write_ndef_records.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ndef_record_scratch {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x54;  /* +0x54  rw=r sz=4 */   <-- NAME ME
};
```