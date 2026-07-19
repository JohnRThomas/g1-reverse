### struct ndef_record_desc  (G1-original)  cid=param_0055

purpose: NDEF record descriptor (pointer/length-style pair) consumed by st25dv_build_and_write_ndef_records when assembling NFC tag records.

This object is accessed by these functions (read their fully-named source):
  - st25dv_build_and_write_ndef_records  (as param_3)  ->  recon/readable_sources/app/g1/st25dv_build_and_write_ndef_records.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ndef_record_desc {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```