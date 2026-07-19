### struct nrfx_qspi_cinstr_config  (library:nrfx_qspi_cinstr_config_t)  cid=param_0339

purpose: nrfx QSPI custom-instruction transfer configuration consumed by nrfx_qspi_cinstr_xfer (opcode/length/IO levels/WREN).

This object is accessed by these functions (read their fully-named source):
  - nrfx_qspi_cinstr_xfer  (as param_1)  ->  recon/readable_sources/app/library/nrfx_qspi_cinstr_xfer.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_qspi_cinstr_config {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
};
```