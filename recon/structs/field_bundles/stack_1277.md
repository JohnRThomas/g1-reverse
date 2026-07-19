### struct panel_temp_calibration_locals  (G1-original)  cid=stack_1277

purpose: Stack-local pair of 16-bit indices used during panel temperature calibration init.

This object is accessed by these functions (read their fully-named source):
  - panel_temp_calibration_init  (as local_32)  ->  recon/readable_sources/app/g1/panel_temp_calibration_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct panel_temp_calibration_locals {
    uint16_t     field_0x0;  /* +0x0  rw=r sz=2 */   <-- NAME ME
    uint16_t     field_0x6;  /* +0x6  rw=r sz=2 */   <-- NAME ME
};
```