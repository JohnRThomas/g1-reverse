### struct bt_conn_ctx  (library:bt_conn)  cid=param_0210

purpose: Bluetooth connection object shared by ble_notify_remote_info_available and bt_smp_request_ltk (SMP/LTK flag bytes near front, status/handle word at 0xc0).

This object is accessed by these functions (read their fully-named source):
  - ble_notify_remote_info_available  (as param_1)  ->  recon/readable_sources/app/g1/ble_notify_remote_info_available.c
  - bt_smp_request_ltk  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_conn_ctx {
    uint8_t      field_0x8;  /* +0x8  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x9;  /* +0x9  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xa;  /* +0xa  rw=w sz=1 */   <-- NAME ME
    uint32_t     field_0xc0;  /* +0xc0  rw=rw sz=4 */   <-- NAME ME
};
```