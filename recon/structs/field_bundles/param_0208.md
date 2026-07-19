### struct bt_conn_le_ctx  (library:bt_conn (internal))  cid=param_0208

purpose: BLE connection object read at LE-param-updated notify (ble_notify_le_param_updated): conn ref + interval/latency/timeout.

This object is accessed by these functions (read their fully-named source):
  - ble_notify_le_param_updated  (as param_1)  ->  recon/readable_sources/app/g1/ble_notify_le_param_updated.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_conn_le_ctx {
    uint32_t     conn_ref;  /* +0x4  rw=r sz=4 */
    uint16_t     le_interval;  /* +0xa6  rw=r sz=2 */
    uint16_t     le_latency;  /* +0xa8  rw=r sz=2 */
    uint16_t     le_timeout;  /* +0xaa  rw=r sz=2 */
    uint16_t     field_0xac;  /* +0xac  rw=r sz=2,4 */   <-- NAME ME
    uint16_t     field_0xae;  /* +0xae  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0xb0;  /* +0xb0  rw=r sz=4 */   <-- NAME ME
};
```