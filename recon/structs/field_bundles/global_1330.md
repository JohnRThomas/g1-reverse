### struct pdm_capture_buffer_state  (G1-original)  cid=global_1330

purpose: Static PDM mic capture buffer/state around nrfx_pdm_stop (global 0x66360): status/count word at each end bracketing a ~0x4f8-byte buffer.

This object is accessed by these functions (read their fully-named source):
  - nrfx_pdm_stop  (as 0x00066360)  ->  recon/readable_sources/app/library/nrfx_pdm_stop.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct pdm_capture_buffer_state {
    uint32_t     field_0x4;  /* +0x4  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x500;  /* +0x500  rw=w sz=4 */   <-- NAME ME
};
```