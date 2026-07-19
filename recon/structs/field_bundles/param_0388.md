### struct lc3_side_data  (library:lc3 side data)  cid=param_0388

purpose: LC3 spectral 'side' encoding data passed to lc3_spec_put_side (param_4).

This object is accessed by these functions (read their fully-named source):
  - lc3_spec_put_side  (as param_4)  ->  recon/readable_sources/app/library/lc3_spec_put_side.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_side_data {
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
};
```