### struct audio_stream_params  (G1-original)  cid=stack_0934

purpose: Local struct in startAudioStreamRecord (local_d8) holding two 16-bit audio parameters.

This object is accessed by these functions (read their fully-named source):
  - startAudioStreamRecord  (as local_d8)  ->  recon/readable_sources/app/g1/startAudioStreamRecord.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct audio_stream_params {
    uint16_t     field_0x0;  /* +0x0  rw=r sz=2 */   <-- NAME ME
    uint16_t     field_0x4;  /* +0x4  rw=r sz=2 */   <-- NAME ME
};
```