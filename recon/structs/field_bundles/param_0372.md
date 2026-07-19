### struct lc3_bitstream_ctx  (library:lc3 decode/bits state)  cid=param_0372

purpose: param_1 of lc3_load_float: LC3 codec bitstream/buffer context (early word + late count word + pointer at 0x4a4).

This object is accessed by these functions (read their fully-named source):
  - lc3_load_float  (as param_1)  ->  recon/readable_sources/app/library/lc3_load_float.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_bitstream_ctx {
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x4a0;  /* +0x4a0  rw=r sz=4 */   <-- NAME ME
    void *       field_0x4a4;  /* +0x4a4  rw=r sz=4 */   <-- NAME ME
};
```