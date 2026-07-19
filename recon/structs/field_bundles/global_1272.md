### struct pdm_mic_event_ctx  (G1-original)  cid=global_1272

purpose: Global PDM microphone driver state used by pdm_mic_event_handler (config/status word plus a trailing status-flag byte).

This object is accessed by these functions (read their fully-named source):
  - pdm_mic_event_handler  (as 0x000600e0)  ->  recon/readable_sources/app/g1/pdm_mic_event_handler.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct pdm_mic_event_ctx {
    uint32_t     field_0x14;  /* +0x14  rw=r sz=4 */   <-- NAME ME
    uint8_t      status_flag;  /* +0x52  rw=r sz=1 */
};
```