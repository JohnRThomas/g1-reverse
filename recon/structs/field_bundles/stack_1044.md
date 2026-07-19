### struct ui_warp_flags_tmp  (G1-original)  cid=stack_1044

purpose: Stack-local flag-byte pair at the tail of a local buffer (local_24) in ui_refalsh_warp.

This object is accessed by these functions (read their fully-named source):
  - ui_refalsh_warp  (as local_24)  ->  recon/readable_sources/app/g1/ui_refalsh_warp.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ui_warp_flags_tmp {
    uint8_t      field_0xe;  /* +0xe  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xf;  /* +0xf  rw=r sz=1 */   <-- NAME ME
};
```