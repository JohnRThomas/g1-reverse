### struct countdown_timer_state  (G1-original)  cid=param_0485

purpose: param_1 of reset_countdown_timer_default: run of four counter/threshold words reset to defaults.

This object is accessed by these functions (read their fully-named source):
  - reset_countdown_timer_default  (as param_1)  ->  recon/readable_sources/app/g1/reset_countdown_timer_default.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct countdown_timer_state {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```