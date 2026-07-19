### struct ipc_static_vrings  (library:struct ipc_static_vrings)  cid=param_0145

purpose: Zephyr ipc_service static_vrings backend instance initialized by ipc_static_vrings_init (vring descriptors, shared-memory addresses, virtqueue/rpmsg config).

This object is accessed by these functions (read their fully-named source):
  - ipc_static_vrings_init  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ipc_static_vrings {
    uint32_t     field_0x18;  /* +0x18  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x20;  /* +0x20  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x28;  /* +0x28  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x2c;  /* +0x2c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x30;  /* +0x30  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x34;  /* +0x34  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x3c;  /* +0x3c  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0x8c;  /* +0x8c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x90;  /* +0x90  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x94;  /* +0x94  rw=r sz=2,4 */   <-- NAME ME
    uint32_t     field_0x98;  /* +0x98  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x9c;  /* +0x9c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xa0;  /* +0xa0  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xa4;  /* +0xa4  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xa8;  /* +0xa8  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xac;  /* +0xac  rw=w sz=4 */   <-- NAME ME
    uint16_t     field_0xb0;  /* +0xb0  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0xb8;  /* +0xb8  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xbc;  /* +0xbc  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xc0;  /* +0xc0  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xc4;  /* +0xc4  rw=w sz=4 */   <-- NAME ME
    uint16_t     field_0xc8;  /* +0xc8  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0xd0;  /* +0xd0  rw=w sz=4 */   <-- NAME ME
    uint32_t     field_0xd4;  /* +0xd4  rw=rw sz=4 */   <-- NAME ME
    uint32_t     field_0xd8;  /* +0xd8  rw=w sz=4 */   <-- NAME ME
};
```