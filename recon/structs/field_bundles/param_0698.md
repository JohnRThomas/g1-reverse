### struct task_ctx_generic  (G1-original)  cid=param_0698

purpose: param_1 of FUN_000855e6: G1 context/config with four leading words plus a pointer at 0x30.

This object is accessed by these functions (read their fully-named source):
  - FUN_000855e6  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct task_ctx_generic {
    int32_t      field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    void *       field_0x30;  /* +0x30  rw=r sz=4 */   <-- NAME ME
};
```