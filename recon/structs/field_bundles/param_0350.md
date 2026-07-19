### struct nrfx_twim_cb  (library:twim_control_block_t (nrfx TWIM))  cid=param_0350

purpose: nrfx TWIM (I2C master) control block used by IRQ handler and transfer-completeness check (handler/ctx, primary/secondary buf ptrs+lengths, address, error byte).

This object is accessed by these functions (read their fully-named source):
  - nrfx_twim_irq_handler  (as param_2)  ->  recon/readable_sources/app/library/nrfx_twim_irq_handler.c
  - xfer_completeness_check  (as param_2)  ->  recon/readable_sources/app/library/xfer_completeness_check.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_twim_cb {
    void*        handler_or_ctx;  /* +0x4  rw=r sz=4 */
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x9;  /* +0x9  rw=w sz=1 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    void*        p_primary_buf;  /* +0x10  rw=r sz=4 */
    uint32_t     primary_length;  /* +0x14  rw=r sz=4 */
    void*        p_secondary_buf;  /* +0x18  rw=r sz=4 */
    uint32_t     secondary_length;  /* +0x1c  rw=r sz=4 */
    uint32_t     address_or_flags;  /* +0x20  rw=r sz=1,4 */
    uint8_t      field_0x23;  /* +0x23  rw=rw sz=1 */   <-- NAME ME
    uint8_t      error_byte;  /* +0x25  rw=r sz=1 */
};
```