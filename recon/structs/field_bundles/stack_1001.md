### struct dashboard_reflash_locals  (G1-original)  cid=stack_1001

purpose: Stack-local state used while rebuilding the dashboard display buffer in DashBoard_Reflash: three leading index words and one trailing word.

This object is accessed by these functions (read their fully-named source):
  - DashBoard_Reflash  (as local_7c)  ->  recon/readable_sources/app/g1/DashBoard_Reflash.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct dashboard_reflash_locals {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x58;  /* +0x58  rw=r sz=4 */   <-- NAME ME
};
```