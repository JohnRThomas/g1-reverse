### struct nrfx_twim_irq_locals  (G1-original)  cid=stack_1351

purpose: Stack-local pair of bytes used inside nrfx_twim_irq_handler while servicing a TWIM interrupt (event/status bytes).

This object is accessed by these functions (read their fully-named source):
  - nrfx_twim_irq_handler  (as local_28)  ->  recon/readable_sources/app/library/nrfx_twim_irq_handler.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_twim_irq_locals {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x4;  /* +0x4  rw=r sz=1 */   <-- NAME ME
};
```