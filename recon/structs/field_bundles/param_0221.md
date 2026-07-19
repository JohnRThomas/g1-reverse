### struct bt_conn_l2cap_view  (library:bt_conn / bt_l2cap_chan)  cid=param_0221

purpose: Large BT connection/channel object shared across l2cap_chan_send_disconnect, l2cap_chan_le_recv_seg, l2cap_le_recv_pdu, gatt_notify_send, gatt_send_service_changed_ind.

This object is accessed by these functions (read their fully-named source):
  - l2cap_chan_send_disconnect  (as param_1)  ->  recon/readable_sources/app/library/l2cap_chan_send_disconnect.c
  - l2cap_chan_le_recv_seg  (as param_1)  ->  recon/readable_sources/app/library/l2cap_chan_le_recv_seg.c
  - l2cap_le_recv_pdu  (as param_1)  ->  recon/readable_sources/app/library/l2cap_le_recv_pdu.c
  - gatt_notify_send  (as param_1)  ->  recon/readable_sources/app/library/gatt_notify_send.c
  - gatt_send_service_changed_ind  (as param_1)  ->  recon/readable_sources/app/library/gatt_send_service_changed_ind.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_conn_l2cap_view {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     handle_or_state;  /* +0x14  rw=r sz=2,4 */
    uint16_t     field_0x16;  /* +0x16  rw=r sz=2 */   <-- NAME ME
    uint16_t     field_0x18;  /* +0x18  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0x1c;  /* +0x1c  rw=r sz=4 */   <-- NAME ME
    uint16_t     att_mtu;  /* +0x21  rw=w sz=2 */
    uint32_t     err_or_id;  /* +0x24  rw=r sz=4 */
    uint8_t      flags_a;  /* +0x2d  rw=rw sz=1 */
    uint8_t      flags_b;  /* +0x2e  rw=w sz=1 */
    uint32_t     field_0x4c;  /* +0x4c  rw=r sz=4 */   <-- NAME ME
    uint32_t     channels_or_state;  /* +0x80  rw=rw sz=4 */
    uint16_t     mtu;  /* +0x84  rw=rw sz=2 */
    uint8_t      field_0xb4;  /* +0xb4  rw=r sz=1 */   <-- NAME ME
    uint16_t     psm_or_cid;  /* +0xb6  rw=r sz=2 */
    uint8_t      field_0xb8;  /* +0xb8  rw=w sz=1 */   <-- NAME ME
};
```