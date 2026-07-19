### struct bt_le_conn_param  (library:bt_le_conn_param)  cid=param_0214

purpose: BLE connection parameters (interval/latency/timeout) shared by send_conn_le_param_update, bt_le_conn_params_valid, bt_conn_le_conn_update.

This object is accessed by these functions (read their fully-named source):
  - send_conn_le_param_update  (as param_2)  ->  recon/readable_sources/app/g1/send_conn_le_param_update.c
  - bt_le_conn_params_valid  (as param_1)  [no source file]
  - bt_conn_le_conn_update  (as param_2)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_le_conn_param {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```