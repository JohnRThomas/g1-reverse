### struct st25dv_ndef_build_ctx_p1  (G1-original)  cid=param_0053

purpose: First pointer argument (param_1) to st25dv_build_and_write_ndef_records; record/context block (8 words) used to assemble NDEF records for the ST25DV NFC tag.

This object is accessed by these functions (read their fully-named source):
  - st25dv_build_and_write_ndef_records  (as param_1)  ->  recon/readable_sources/app/g1/st25dv_build_and_write_ndef_records.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct st25dv_ndef_build_ctx_p1 {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
};
```