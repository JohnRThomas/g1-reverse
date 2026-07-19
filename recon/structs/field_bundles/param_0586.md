### struct bt_le_conn_param  (library:struct bt_le_conn_param)  cid=param_0586

purpose: BLE connection-parameter set passed to bt_conn_le_param_update (interval/latency/timeout).

This object is accessed by these functions (read their fully-named source):
  - bt_conn_le_param_update  (as param_2)  ->  recon/readable_sources/app/library/bt_conn_le_param_update.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_le_conn_param {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```