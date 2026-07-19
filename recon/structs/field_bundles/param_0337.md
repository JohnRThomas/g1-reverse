### struct qspi_pins_config  (library:nrf_qspi_pins_t)  cid=param_0337

purpose: QSPI pin-assignment argument to nrf_qspi_pins_set (sck/csn/io0-io3).

This object is accessed by these functions (read their fully-named source):
  - nrf_qspi_pins_set  (as param_1)  ->  recon/readable_sources/app/library/nrf_qspi_pins_set.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct qspi_pins_config {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
};
```