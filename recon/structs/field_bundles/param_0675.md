### struct driver_cb_ctx  (G1-original)  cid=param_0675

purpose: G1-original driver callback-registration context (callback ptr + word) used by driver_register_callback_locked.

This object is accessed by these functions (read their fully-named source):
  - driver_register_callback_locked  (as param_1)  ->  recon/readable_sources/app/g1/driver_register_callback_locked.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct driver_cb_ctx {
    void *       callback;  /* +0x4  rw=r sz=4 */
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```