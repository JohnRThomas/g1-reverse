### struct nrfx_spim_t  (library:nrfx_spim_t)  cid=param_0342

purpose: nrfx SPIM peripheral instance handle used by nrfx_spim_configure/nrfx_spim_init: a driver-instance index byte plus a byte read at 0x4.

This object is accessed by these functions (read their fully-named source):
  - nrfx_spim_configure  (as param_1)  ->  recon/readable_sources/app/library/nrfx_spim_configure.c
  - nrfx_spim_init  (as param_1)  ->  recon/readable_sources/app/library/nrfx_spim_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_spim_t {
    uint8_t      field_0x1;  /* +0x1  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x4;  /* +0x4  rw=r sz=1 */   <-- NAME ME
};
```