### struct deferred_call_pair_ctx  (G1-original)  cid=param_0436

purpose: Deferred call-pair setup context used by setup_deferred_call_pair (three words).

This object is accessed by these functions (read their fully-named source):
  - setup_deferred_call_pair  (as param_1)  ->  recon/readable_sources/app/library/setup_deferred_call_pair.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct deferred_call_pair_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```