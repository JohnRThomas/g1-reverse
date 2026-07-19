### struct ble_conn_complete_ctx  (G1-original)  cid=param_0215

purpose: BLE connection completion/disconnection processing context (ble_conn_process_complete_or_disconnect); two words within a connection-info object.

This object is accessed by these functions (read their fully-named source):
  - ble_conn_process_complete_or_disconnect  (as param_1)  ->  recon/readable_sources/app/g1/ble_conn_process_complete_or_disconnect.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ble_conn_complete_ctx {
    uint32_t     field_0x48;  /* +0x48  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x50;  /* +0x50  rw=r sz=4 */   <-- NAME ME
};
```