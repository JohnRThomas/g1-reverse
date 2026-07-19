### struct net_buf_simple  (library:struct net_buf_simple)  cid=param_0285

purpose: Zephyr net_buf_simple passed to net_buf_simple_push (data pointer / len / size / __buf).

This object is accessed by these functions (read their fully-named source):
  - net_buf_simple_push  (as param_1)  ->  recon/readable_sources/app/library/net_buf_simple_push.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct net_buf_simple {
    uint16_t     field_0x1;  /* +0x1  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```