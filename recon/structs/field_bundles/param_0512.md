### struct log_output_ctx  (library:log_output)  cid=param_0512

purpose: Zephyr logging output context flushed by log_output_flush.

This object is accessed by these functions (read their fully-named source):
  - log_output_flush  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct log_output_ctx {
    uint32_t     field_0x0;  /* +0x0  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```