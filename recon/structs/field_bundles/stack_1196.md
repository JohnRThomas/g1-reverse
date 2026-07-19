### struct bt_att_accept_locals  (G1-original)  cid=stack_1196

purpose: Large local frame in bt_att_accept setting up an incoming ATT connection (two 16-bit setup fields + trailing word).

This object is accessed by these functions (read their fully-named source):
  - bt_att_accept  (as local_1c)  ->  recon/readable_sources/app/library/bt_att_accept.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_att_accept_locals {
    uint16_t     field_0x1e;  /* +0x1e  rw=w sz=2 */   <-- NAME ME
    uint16_t     field_0x2e;  /* +0x2e  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0x120;  /* +0x120  rw=r sz=4 */   <-- NAME ME
};
```