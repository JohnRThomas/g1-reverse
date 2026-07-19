### struct nrfx_qspi_cb  (library:nrfx_qspi control block)  cid=global_1344

purpose: nrfx QSPI driver control block, accessed by nrfx_qspi_cinstr_xfer during a custom-instruction transfer.

This object is accessed by these functions (read their fully-named source):
  - nrfx_qspi_cinstr_xfer  (as 0x00066adc)  ->  recon/readable_sources/app/library/nrfx_qspi_cinstr_xfer.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_qspi_cb {
    uint8_t      field_0x30;  /* +0x30  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x38;  /* +0x38  rw=r sz=1 */   <-- NAME ME
};
```