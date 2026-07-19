### struct context_release_ctx  (G1-original)  cid=param_0592

purpose: Context object released/notified via context_release_and_notify: leading callback ptr, flags, and a semaphore/event value near the end.

This object is accessed by these functions (read their fully-named source):
  - context_release_and_notify  (as param_1)  ->  recon/readable_sources/app/g1/context_release_and_notify.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct context_release_ctx {
    void *       callback_fn;  /* +0x0  rw=r sz=4 */
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x2d;  /* +0x2d  rw=w sz=1 */   <-- NAME ME
    uint16_t     field_0xb6;  /* +0xb6  rw=w sz=2 */   <-- NAME ME
};
```