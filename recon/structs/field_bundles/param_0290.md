### struct adc_channel_cfg  (library:adc_channel_cfg)  cid=param_0290

purpose: ADC channel configuration descriptor passed as the cfg argument to adc_channel_config (gain/reference/acquisition-time/channel/inputs).

This object is accessed by these functions (read their fully-named source):
  - adc_channel_config  (as param_2)  ->  recon/readable_sources/app/g1/adc_channel_config.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct adc_channel_cfg {
    uint16_t     acquisition_time;  /* +0x2  rw=r sz=2 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
};
```