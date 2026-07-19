### struct nrfx_qspi_cb  (library:nrfx_qspi control block (nrfx_qspi_cb))  cid=global_1562

purpose: nrfx QSPI driver control-block / state referenced by nrfx_qspi_write; two index words read at 0x30 and 0x38 (global base 0x6661c).

This object is accessed by these functions (read their fully-named source):
  - nrfx_qspi_write  (as 0x0006661c)  ->  recon/readable_sources/app/library/nrfx_qspi_write.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_qspi_cb {
    uint32_t     field_0x30;  /* +0x30  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x38;  /* +0x38  rw=r sz=4 */   <-- NAME ME
};
```