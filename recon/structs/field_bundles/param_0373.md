### struct lc3_encoder_ctx  (library:struct lc3_encoder (liblc3))  cid=param_0373

purpose: LC3 codec encoder state (param_1) passed to lc3_encode: frame-config words near the start and derived analysis outputs near the end.

This object is accessed by these functions (read their fully-named source):
  - lc3_encode  (as param_1)  ->  recon/readable_sources/app/library/lc3_encode.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_encoder_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4a0;  /* +0x4a0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4a4;  /* +0x4a4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4a8;  /* +0x4a8  rw=r sz=4 */   <-- NAME ME
};
```