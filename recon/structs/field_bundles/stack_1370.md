### struct lc3_ltpf_pitch_buf  (library:liblc3 ltpf pitch buffer)  cid=stack_1370

purpose: Stack local (local_1b0) in lc3_ltpf_detect_pitch: LC3 long-term pitch prediction working buffer (correlation/energy array).

This object is accessed by these functions (read their fully-named source):
  - lc3_ltpf_detect_pitch  (as local_1b0)  ->  recon/readable_sources/app/library/lc3_ltpf_detect_pitch.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct lc3_ltpf_pitch_buf {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18c;  /* +0x18c  rw=r sz=4 */   <-- NAME ME
};
```