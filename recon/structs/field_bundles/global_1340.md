### struct nrfx_qspi_control_block  (library:nrfx_qspi_cb_t (internal))  cid=global_1340

purpose: nrfx QSPI driver internal control block (static singleton); tail fields 0x524-0x53c touched by qspi_workaround_apply (nRF5340 QSPI erratum patch) and nrfx_qspi_uninit.

This object is accessed by these functions (read their fully-named source):
  - qspi_workaround_apply  (as 0x0006684c)  ->  recon/readable_sources/app/library/qspi_workaround_apply.c
  - nrfx_qspi_uninit  (as 0x00066bc0)  ->  recon/readable_sources/app/library/nrfx_qspi_uninit.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_qspi_control_block {
    uint32_t     field_0x524;  /* +0x524  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x528;  /* +0x528  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x530;  /* +0x530  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x534;  /* +0x534  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x538;  /* +0x538  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x53c;  /* +0x53c  rw=r sz=4 */   <-- NAME ME
};
```