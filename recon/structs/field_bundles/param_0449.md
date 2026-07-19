### struct llf_rnd_state  (library:LLF_RND_State_t / CC RND HAL state)  cid=param_0449

purpose: CryptoCell low-level RND (ring-oscillator) state read by LLF_RND_GetRoscSampleCnt (sample-count field at +0x24).

This object is accessed by these functions (read their fully-named source):
  - LLF_RND_GetRoscSampleCnt  (as param_2)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct llf_rnd_state {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     rosc_sample_cnt;  /* +0x24  rw=r sz=4 */
};
```