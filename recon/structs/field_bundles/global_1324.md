### struct nrfx_pdm_cb  (library:nrfx_pdm control block (m_cb))  cid=global_1324

purpose: nrfx PDM driver control-block/state (0x661cc) accessed by nrfx_pdm_init; two index/handle words observed.

This object is accessed by these functions (read their fully-named source):
  - nrfx_pdm_init  (as 0x000661cc)  ->  recon/readable_sources/app/library/nrfx_pdm_init.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct nrfx_pdm_cb {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```