### struct bt_conn  (library:bt_conn)  cid=param_0248

purpose: Zephyr Bluetooth connection object shared across GATT service-change/CCC/indicate/notify and library bt_conn_* helpers; assorted flag bytes plus an int at 0xc0.

This object is accessed by these functions (read their fully-named source):
  - sc_clear  (as param_1)  ->  recon/readable_sources/app/g1/sc_clear.c
  - gatt_remove_peer_from_attr  (as param_3)  ->  recon/readable_sources/app/library/gatt_remove_peer_from_attr.c
  - gatt_ccc_write  (as param_1)  ->  recon/readable_sources/app/library/gatt_ccc_write.c
  - gatt_find_ccc_for_conn  (as param_1)  ->  recon/readable_sources/app/library/gatt_find_ccc_for_conn.c
  - bt_gatt_indicate  (as param_1)  ->  recon/readable_sources/app/library/bt_gatt_indicate.c
  - bt_gatt_notify_cb  (as param_1)  ->  recon/readable_sources/app/library/bt_gatt_notify_cb.c
  - bt_conn_ltk_present  (as param_1)  [no source file]
  - bt_conn_is_peer_addr_le  (as param_1)  [no source file]
  - bt_gatt_check_perm  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_conn {
    uint8_t      field_0x3;  /* +0x3  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x8;  /* +0x8  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xb;  /* +0xb  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xd;  /* +0xd  rw=r sz=1 */   <-- NAME ME
    int32_t      field_0xc0;  /* +0xc0  rw=r sz=4 */   <-- NAME ME
};
```