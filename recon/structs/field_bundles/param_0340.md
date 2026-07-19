### struct nrfx_pin_freq_cfg  (library:nrfx pin/freq config)  cid=param_0340

purpose: Pin/frequency validation configuration (param_2) passed to nrfx_pin_freq_config_validate (QSPI pin config).

This object is accessed by these functions (read their fully-named source):
  - nrfx_pin_freq_config_validate  (as param_2)  ->  recon/readable_sources/app/library/nrfx_pin_freq_config_validate.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_pin_freq_cfg {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x21;  /* +0x21  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x23;  /* +0x23  rw=r sz=1 */   <-- NAME ME
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
};
```