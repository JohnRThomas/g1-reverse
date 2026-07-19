### struct dma_xfer_desc  (G1-original)  cid=param_0705

purpose: DMA transfer descriptor handled by dma_xfer_end_handler (leading callback/opcode word plus several state words).

This object is accessed by these functions (read their fully-named source):
  - dma_xfer_end_handler  (as param_1)  ->  recon/readable_sources/app/g1/dma_xfer_end_handler.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct dma_xfer_desc {
    uint32_t     cb_or_opcode;  /* +0x0  rw=r sz=2,4 */
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x26;  /* +0x26  rw=rw sz=2 */   <-- NAME ME
};
```