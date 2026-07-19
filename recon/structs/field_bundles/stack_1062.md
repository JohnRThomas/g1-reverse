### struct scratch_ctx_0004cf78  (G1-original)  cid=stack_1062

purpose: Local scratch aggregate in FUN_0004cf78: a write-only status byte + three read-only words across a large frame.

This object is accessed by these functions (read their fully-named source):
  - FUN_0004cf78  (as local_24)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct scratch_ctx_0004cf78 {
    uint8_t      field_0x19;  /* +0x19  rw=w sz=1 */   <-- NAME ME
    int32_t      field_0x3c;  /* +0x3c  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x68;  /* +0x68  rw=r sz=4 */   <-- NAME ME
    int32_t      field_0x6c;  /* +0x6c  rw=r sz=4 */   <-- NAME ME
};
```