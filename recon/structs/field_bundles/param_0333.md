### struct pdm_pin_config  (G1-original)  cid=param_0333

purpose: PDM GPIO pin configuration (clock/data pin numbers and related fields) consumed by pdm_configure_pins.

This object is accessed by these functions (read their fully-named source):
  - pdm_configure_pins  (as param_1)  ->  recon/readable_sources/app/g1/pdm_configure_pins.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct pdm_pin_config {
    uint32_t     pin_clk;  /* +0x4  rw=r sz=4 */
    uint32_t     pin_din;  /* +0x8  rw=r sz=4 */
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x40;  /* +0x40  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x44;  /* +0x44  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4c;  /* +0x4c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x50;  /* +0x50  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x54;  /* +0x54  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x58;  /* +0x58  rw=r sz=4 */   <-- NAME ME
};
```