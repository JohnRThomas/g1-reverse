### struct bt_att_chan  (library:struct bt_att_chan)  cid=param_0227

purpose: Zephyr ATT channel object used by bt_att_chan_create_pdu (MTU fields near +0x1e/+0x2e, plus two words at struct tail).

This object is accessed by these functions (read their fully-named source):
  - bt_att_chan_create_pdu  (as param_1)  ->  recon/readable_sources/app/library/bt_att_chan_create_pdu.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_att_chan {
    uint16_t     field_0x1e;  /* +0x1e  rw=r sz=2 */   <-- NAME ME
    uint16_t     field_0x2e;  /* +0x2e  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0x144;  /* +0x144  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x148;  /* +0x148  rw=r sz=4 */   <-- NAME ME
};
```