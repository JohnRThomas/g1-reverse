### struct bt_att_chan  (library:bt_att_chan)  cid=param_0606

purpose: Zephyr ATT channel context used by att_chan_read: an MTU field and a pending handle/offset field.

This object is accessed by these functions (read their fully-named source):
  - att_chan_read  (as param_1)  ->  recon/readable_sources/app/library/att_chan_read.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_att_chan {
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint16_t     mtu;  /* +0x1e  rw=r sz=2 */
    uint16_t     handle_or_offset;  /* +0x2e  rw=r sz=2 */
};
```