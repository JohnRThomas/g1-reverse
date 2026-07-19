### struct bt_conn  (library:bt_conn)  cid=global_1185

purpose: Zephyr Bluetooth connection object (global connection pool slot); the two observed fields are in the TX/state tail region accessed by bt_conn_prepare_tx_events.

This object is accessed by these functions (read their fully-named source):
  - bt_conn_prepare_tx_events  (as 0x0005664c)  ->  recon/readable_sources/app/library/bt_conn_prepare_tx_events.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_conn {
    uint16_t     field_0x104;  /* +0x104  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0x110;  /* +0x110  rw=r sz=4 */   <-- NAME ME
};
```