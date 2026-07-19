### struct bt_conn  (library:bt_conn)  cid=param_0034

purpose: Zephyr Bluetooth connection object (bt_conn) — type/role, handle, ref/state, TX queues, L2CAP channel list, LE connection parameters, and security level, shared across 21 host functions.

This object is accessed by these functions (read their fully-named source):
  - ancs_connected  (as param_1)  ->  recon/readable_sources/app/g1/ancs_connected.c
  - bt_conn_notify_connected  (as param_1)  ->  recon/readable_sources/app/library/bt_conn_notify_connected.c
  - tx_notify  (as param_1)  ->  recon/readable_sources/app/library/tx_notify.c
  - conn_tx_send_to_driver  (as param_1)  ->  recon/readable_sources/app/g1/conn_tx_send_to_driver.c
  - bt_conn_tx_drain_and_reset  (as param_1)  ->  recon/readable_sources/app/library/bt_conn_tx_drain_and_reset.c
  - bt_acl_data_recv  (as param_1)  ->  recon/readable_sources/app/g1/bt_acl_data_recv.c
  - ble_conn_unref  (as param_1)  ->  recon/readable_sources/app/g1/ble_conn_unref.c
  - ble_conn_set_state  (as param_1)  ->  recon/readable_sources/app/g1/ble_conn_set_state.c
  - bt_conn_disconnect_by_state  (as param_1)  ->  recon/readable_sources/app/library/bt_conn_disconnect_by_state.c
  - send_conn_le_param_update  (as param_1)  ->  recon/readable_sources/app/g1/send_conn_le_param_update.c
  - bt_conn_tx_process  (as param_1)  ->  recon/readable_sources/app/library/bt_conn_tx_process.c
  - l2cap_chan_add  (as param_1)  ->  recon/readable_sources/app/library/l2cap_chan_add.c
  - att_get  (as param_1)  ->  recon/readable_sources/app/library/att_get.c
  - smp_send_security_req  (as param_1)  ->  recon/readable_sources/app/library/smp_send_security_req.c
  - bt_conn_reset_rx_state  (as param_1)  [no source file]
  - FUN_0008142c  (as param_1)  [no source file]
  - g1_recon_bt_conn_set_security  (as param_1)  ->  recon/readable_sources/app/library/g1_recon_bt_conn_set_security.c
  - bt_conn_get_security  (as param_1)  ->  recon/readable_sources/app/library/bt_conn_get_security.c
  - bt_conn_le_param_update  (as param_1)  ->  recon/readable_sources/app/library/bt_conn_le_param_update.c
  - bt_conn_create_pdu  (as param_1)  ->  recon/readable_sources/app/library/bt_conn_create_pdu.c
  - bt_l2cap_le_lookup_rx_cid  (as param_1)  ->  recon/readable_sources/app/library/bt_l2cap_le_lookup_rx_cid.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_conn {
    uint8_t      type_or_role;  /* +0x1  rw=r sz=1 */
    uint16_t     handle;  /* +0x2  rw=r sz=1,2 */
    uint8_t      field_0x3;  /* +0x3  rw=r sz=1 */   <-- NAME ME
    uint32_t     state_or_ref;  /* +0x4  rw=rw sz=4 */
    uint8_t      field_0x6;  /* +0x6  rw=w sz=1 */   <-- NAME ME
    uint8_t      field_0x8;  /* +0x8  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x9;  /* +0x9  rw=r sz=1 */   <-- NAME ME
    void *       field_0xa;  /* +0xa  rw=rw sz=1,4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=rw sz=1,4 */   <-- NAME ME
    uint8_t      field_0xd;  /* +0xd  rw=rw sz=1 */   <-- NAME ME
    uint32_t     field_0xe;  /* +0xe  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=rw sz=4 */   <-- NAME ME
    void *       tx_pending_list_head;  /* +0x14  rw=rw sz=4 */
    void *       tx_notify_list_head;  /* +0x18  rw=rw sz=4 */
    uint32_t     tx_data_count;  /* +0x1c  rw=rw sz=4 */
    void *       channel_list_head;  /* +0x20  rw=rw sz=4 */
    void *       le_param_or_role_ptr;  /* +0x24  rw=rw sz=4 */
    void *       field_0x54;  /* +0x54  rw=rw sz=4 */   <-- NAME ME
    void *       field_0x58;  /* +0x58  rw=rw sz=4 */   <-- NAME ME
    uint16_t     le_interval;  /* +0xa6  rw=r sz=2 */
    uint16_t     le_latency;  /* +0xa8  rw=w sz=2 */
    uint16_t     le_timeout;  /* +0xaa  rw=w sz=2 */
    uint16_t     le_interval_min;  /* +0xac  rw=r sz=2 */
    uint16_t     le_interval_max;  /* +0xae  rw=r sz=2 */
    uint16_t     le_pending_latency;  /* +0xb0  rw=w sz=2 */
    uint16_t     le_pending_timeout;  /* +0xb2  rw=w sz=2 */
    uint8_t      security_level;  /* +0xb4  rw=w sz=1 */
    uint8_t      security_flags;  /* +0xb5  rw=r sz=1 */
    uint32_t     field_0xc0;  /* +0xc0  rw=rw sz=4 */   <-- NAME ME
};
```