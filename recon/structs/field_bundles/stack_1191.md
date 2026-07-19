### struct l2cap_connected_locals  (G1-original)  cid=stack_1191

purpose: Stack-local L2CAP LE channel setup values (local_14) in bt_l2cap_connected (channel pointer, MTU word, two 16-bit fields).

This object is accessed by these functions (read their fully-named source):
  - bt_l2cap_connected  (as local_14)  ->  recon/readable_sources/app/library/bt_l2cap_connected.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct l2cap_connected_locals {
    void *       chan;  /* +0x4  rw=r sz=4 */
    uint32_t     mtu;  /* +0x10  rw=rw sz=4 */
    uint16_t     field_0x14;  /* +0x14  rw=w sz=2 */   <-- NAME ME
    uint16_t     field_0x24;  /* +0x24  rw=w sz=2 */   <-- NAME ME
};
```