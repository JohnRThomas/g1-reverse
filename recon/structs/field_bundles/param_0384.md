### struct lc3_sns_state  (G1-original)  cid=param_0384

purpose: LC3 codec SNS (spectral noise shaping) analysis state shared by lc3_sns_analyze (param_5) and lc3_sns_put_data (param_2).

This object is accessed by these functions (read their fully-named source):
  - lc3_sns_analyze  (as param_5)  ->  recon/readable_sources/app/library/lc3_sns_analyze.c
  - lc3_sns_put_data  (as param_2)  ->  recon/readable_sources/app/library/lc3_sns_put_data.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_sns_state {
    uint16_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x6;  /* +0x6  rw=rw sz=1 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint8_t      flag_byte;  /* +0x19  rw=rw sz=1 */
};
```