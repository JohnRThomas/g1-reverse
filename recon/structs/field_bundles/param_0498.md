### struct sys_notify  (library:sys_notify)  cid=param_0498

purpose: Zephyr sys_notify async-operation notification object validated by sys_notify_validate: method union (signal/callback) and flags word.

This object is accessed by these functions (read their fully-named source):
  - sys_notify_validate  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct sys_notify {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```