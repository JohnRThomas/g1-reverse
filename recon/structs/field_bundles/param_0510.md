### struct cbprintf_cpy_ctx  (library:cbprintf cpy context)  cid=param_0510

purpose: Zephyr cbprintf internal copy descriptor (param_3) used by z_cbprintf_cpy: destination/length pair.

This object is accessed by these functions (read their fully-named source):
  - z_cbprintf_cpy  (as param_3)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct cbprintf_cpy_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```