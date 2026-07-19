### struct lc3_bits_t  (library:lc3_bits_t)  cid=param_0366

purpose: LC3 codec bitstream writer/reader state shared across lc3_put_bits_generic/ac_write_renorm/ltpf/sns/spec/tns put helpers: counters/accumulators plus buffer pointers.

This object is accessed by these functions (read their fully-named source):
  - lc3_get_bits_left  (as param_1)  ->  recon/readable_sources/app/library/lc3_get_bits_left.c
  - lc3_put_bits_generic  (as param_1)  ->  recon/readable_sources/app/library/lc3_put_bits_generic.c
  - lc3_ac_write_renorm  (as param_1)  ->  recon/readable_sources/app/library/lc3_ac_write_renorm.c
  - lc3_ltpf_put_data  (as param_1)  ->  recon/readable_sources/app/library/lc3_ltpf_put_data.c
  - lc3_sns_put_data  (as param_1)  ->  recon/readable_sources/app/library/lc3_sns_put_data.c
  - lc3_spec_put_side  (as param_1)  ->  recon/readable_sources/app/library/lc3_spec_put_side.c
  - lc3_spec_encode  (as param_1)  ->  recon/readable_sources/app/library/lc3_spec_encode.c
  - lc3_tns_put_data  (as param_1)  ->  recon/readable_sources/app/library/lc3_tns_put_data.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_bits_t {
    uint32_t     nbits_or_pos;  /* +0x4  rw=rw sz=4 */
    uint32_t     cache;  /* +0x8  rw=rw sz=4 */
    uint32_t     field_0xc;  /* +0xc  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
    uint8_t*     buffer;  /* +0x2c  rw=r sz=4 */
    uint8_t*     buffer_cursor;  /* +0x30  rw=rw sz=4 */
    uint32_t     field_0x34;  /* +0x34  rw=rw sz=4 */   <-- NAME ME
};
```