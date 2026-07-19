### struct nrfx_twim_control_block  (library:twim_control_block (nrfx_twim.c))  cid=param_0349

purpose: nrfx TWIM (I2C master) driver control block (config, transfer descriptors, IRQ context) used by nrfx_twim_irq_handler/nrfx_twim_xfer/xfer_completeness_check.

This object is accessed by these functions (read their fully-named source):
  - nrfx_twim_irq_handler  (as param_1)  ->  recon/readable_sources/app/library/nrfx_twim_irq_handler.c
  - nrfx_twim_xfer  (as param_1)  ->  recon/readable_sources/app/library/nrfx_twim_xfer.c
  - xfer_completeness_check  (as param_1)  ->  recon/readable_sources/app/library/xfer_completeness_check.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_twim_control_block {
    uint8_t      drv_state;  /* +0x1  rw=r sz=1 */
    uint32_t     p_reg_or_addr;  /* +0x8  rw=rw sz=4 */
    uint32_t     field_0x14;  /* +0x14  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x104;  /* +0x104  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x124;  /* +0x124  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x148;  /* +0x148  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x15c;  /* +0x15c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x160;  /* +0x160  rw=rw sz=4 */   <-- NAME ME
    uint32_t     xfer_flags;  /* +0x200  rw=rw sz=4 */
    uint32_t     field_0x304;  /* +0x304  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x308;  /* +0x308  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x4c4;  /* +0x4c4  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0x500;  /* +0x500  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x534;  /* +0x534  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x538;  /* +0x538  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x53c;  /* +0x53c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x540;  /* +0x540  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x544;  /* +0x544  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x548;  /* +0x548  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x54c;  /* +0x54c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x550;  /* +0x550  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x588;  /* +0x588  rw=r sz=4 */   <-- NAME ME
};
```