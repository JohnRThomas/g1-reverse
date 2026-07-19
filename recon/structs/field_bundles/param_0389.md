### struct lc3_spec_encode_ctx  (library:liblc3 internal (lc3_spec_encode arg))  cid=param_0389

purpose: Small scalar/flag parameter block passed to lc3_spec_encode (LC3 spectral encoding).

This object is accessed by these functions (read their fully-named source):
  - lc3_spec_encode  (as param_7)  ->  recon/readable_sources/app/library/lc3_spec_encode.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_spec_encode_ctx {
    int32_t      field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint8_t      flag_0x8;  /* +0x8  rw=r sz=1 */
};
```