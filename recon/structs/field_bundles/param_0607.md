### struct cmd_ctx_0607  (G1-original)  cid=param_0607

purpose: Unidentified small G1 context (flag byte + two words) used inside FUN_00081fbe.

This object is accessed by these functions (read their fully-named source):
  - FUN_00081fbe  (as param_3)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct cmd_ctx_0607 {
    uint8_t      field_0x3;  /* +0x3  rw=w sz=1 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```