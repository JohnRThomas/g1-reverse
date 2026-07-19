### struct uarte_nrfx_data  (library:uarte_nrfx driver data (uarte_nrfx_uarte.c internal))  cid=param_0312

purpose: nrfx UARTE driver instance data used by uarte_nrfx_configure and uarte_nrfx_init; two pointer fields observed.

This object is accessed by these functions (read their fully-named source):
  - uarte_nrfx_configure  (as param_1)  ->  recon/readable_sources/app/library/uarte_nrfx_configure.c
  - uarte_nrfx_init  (as param_1)  ->  recon/readable_sources/app/g1/uarte_nrfx_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct uarte_nrfx_data {
    void *       field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    void *       field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```