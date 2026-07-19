### struct pdm_mic_event_data  (G1-original)  cid=stack_1273

purpose: Stack-local PDM microphone event data in pdm_mic_event_handler: a buffer pointer/index and a size/status word.

This object is accessed by these functions (read their fully-named source):
  - pdm_mic_event_handler  (as local_30)  ->  recon/readable_sources/app/g1/pdm_mic_event_handler.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct pdm_mic_event_data {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```