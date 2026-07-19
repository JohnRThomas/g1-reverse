### struct ui_refresh_warp_state  (G1-original)  cid=global_1046

purpose: Global UI refresh/warp control state (0x40190) read by ui_refalsh_warp.

This object is accessed by these functions (read their fully-named source):
  - ui_refalsh_warp  (as 0x00040190)  ->  recon/readable_sources/app/g1/ui_refalsh_warp.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ui_refresh_warp_state {
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
};
```