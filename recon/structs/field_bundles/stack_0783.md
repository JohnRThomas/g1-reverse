### struct fuel_gauge_reading  (G1-original)  cid=stack_0783

purpose: Stack-local index/value pair in fuel_gauge_update (local_3c).

This object is accessed by these functions (read their fully-named source):
  - fuel_gauge_update  (as local_3c)  ->  recon/readable_sources/app/g1/fuel_gauge_update.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct fuel_gauge_reading {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```