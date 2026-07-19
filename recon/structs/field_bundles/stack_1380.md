### struct lc3_sns_analyze_buf  (G1-original)  cid=stack_1380

purpose: Local 0xfc-byte SNS analysis buffer in lc3_sns_analyze (local_268): leading index and trailing result.

This object is accessed by these functions (read their fully-named source):
  - lc3_sns_analyze  (as local_268)  ->  recon/readable_sources/app/library/lc3_sns_analyze.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_sns_analyze_buf {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xf8;  /* +0xf8  rw=r sz=4 */   <-- NAME ME
};
```