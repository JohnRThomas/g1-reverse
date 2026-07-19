### struct pair_ctx_0503  (G1-original)  cid=param_0503

purpose: Small two-word object (0x4/0x8) used only within FUN_0007e6a6; insufficient naming signal.

This object is accessed by these functions (read their fully-named source):
  - FUN_0007e6a6  (as param_2)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct pair_ctx_0503 {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```