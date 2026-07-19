### struct bt_att_accept_local  (library:bt_l2cap_chan / bt_att_chan)  cid=stack_1197

purpose: Stack local (local_20) in bt_att_accept: on-stack channel/context object populated before the accept path (two early words + a block at 0x28-0x34).

This object is accessed by these functions (read their fully-named source):
  - bt_att_accept  (as local_20)  ->  recon/readable_sources/app/library/bt_att_accept.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_att_accept_local {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x28;  /* +0x28  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x2c;  /* +0x2c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x30;  /* +0x30  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x34;  /* +0x34  rw=r sz=4 */   <-- NAME ME
};
```