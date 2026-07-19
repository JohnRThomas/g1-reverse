### struct spi_master_ops  (G1-original)  cid=param_0067

purpose: G1-original two-word ops/context block passed to spi_master_install_ops (SPI master driver op-table slots).

This object is accessed by these functions (read their fully-named source):
  - spi_master_install_ops  (as param_1)  ->  recon/readable_sources/app/g1/spi_master_install_ops.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct spi_master_ops {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```