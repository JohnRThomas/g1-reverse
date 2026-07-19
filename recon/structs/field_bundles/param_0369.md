### struct lc3_encoder_state  (library:liblc3 encoder/decoder state (internal))  cid=param_0369

purpose: LC3 codec context passed to lc3_load_s24_3le: a small header field plus a count and buffer pointer after a large sample buffer region.

This object is accessed by these functions (read their fully-named source):
  - lc3_load_s24_3le  (as param_1)  ->  recon/readable_sources/app/library/lc3_load_s24_3le.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_encoder_state {
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    int32_t      sample_count_or_stride;  /* +0x4a0  rw=r sz=4 */
    void *       buf_ptr;  /* +0x4a4  rw=r sz=4 */
};
```