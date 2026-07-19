### struct record_type8_ctx  (G1-original)  cid=param_0052

purpose: G1-original type-8 record builder context used by fill_record_type8: a type byte and a value word.

This object is accessed by these functions (read their fully-named source):
  - fill_record_type8  (as param_2)  ->  recon/readable_sources/app/g1/fill_record_type8.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct record_type8_ctx {
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
};
```