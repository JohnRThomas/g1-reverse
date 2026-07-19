### struct generic_handle_ctx  (G1-original)  cid=param_0505

purpose: G1-original context object read by FUN_0007eb5c: a pointer field and a separate int field.

This object is accessed by these functions (read their fully-named source):
  - FUN_0007eb5c  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct generic_handle_ctx {
    void *       field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```