### struct bt_l2cap_chan_ctx  (library:bt_l2cap_chan (internal))  cid=param_0597

purpose: L2CAP channel context passed to l2cap_chan_disconnected_cb (state u16 + ptr + word).

This object is accessed by these functions (read their fully-named source):
  - l2cap_chan_disconnected_cb  (as param_2)  ->  recon/readable_sources/app/library/l2cap_chan_disconnected_cb.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_l2cap_chan_ctx {
    uint16_t     field_0x4;  /* +0x4  rw=r sz=2 */   <-- NAME ME
    void *       field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```