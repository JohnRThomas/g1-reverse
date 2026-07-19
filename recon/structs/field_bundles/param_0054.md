### struct st25dv_ndef_build_ctx_p2  (G1-original)  cid=param_0054

purpose: Second pointer argument (param_2) to st25dv_build_and_write_ndef_records; an 8-word context/record block used while assembling NDEF records for the ST25DV NFC tag.

This object is accessed by these functions (read their fully-named source):
  - st25dv_build_and_write_ndef_records  (as param_2)  ->  recon/readable_sources/app/g1/st25dv_build_and_write_ndef_records.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct st25dv_ndef_build_ctx_p2 {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=r sz=4 */   <-- NAME ME
};
```