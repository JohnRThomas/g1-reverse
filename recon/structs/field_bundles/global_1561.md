### struct nrfx_qspi_write_region  (library:nrfx_qspi (write region))  cid=global_1561

purpose: QSPI write region / register+EasyDMA block (global 0x66630) written by nrfx_qspi_write: task/trigger word at 0x100 and config/status words at 0x504/0x510.

This object is accessed by these functions (read their fully-named source):
  - nrfx_qspi_write  (as 0x00066630)  ->  recon/readable_sources/app/library/nrfx_qspi_write.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_qspi_write_region {
    uint32_t     field_0x100;  /* +0x100  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x504;  /* +0x504  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x510;  /* +0x510  rw=w sz=4 */   <-- NAME ME
};
```