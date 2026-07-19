### struct sett_init_params  (G1-original)  cid=param_0041

purpose: Initialization parameter block consumed by sett_init to configure a settings entry (three read words).

This object is accessed by these functions (read their fully-named source):
  - sett_init  (as param_1)  ->  recon/readable_sources/app/g1/sett_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct sett_init_params {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```