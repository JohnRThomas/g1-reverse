### struct ble_conn_addr_params  (G1-original)  cid=param_0200

purpose: param_1 of ble_conn_addr_and_params_valid: validates a BLE peer address + connection parameters (type/value words plus a role/status int).

This object is accessed by these functions (read their fully-named source):
  - ble_conn_addr_and_params_valid  (as param_1)  ->  recon/readable_sources/app/g1/ble_conn_addr_and_params_valid.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ble_conn_addr_params {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    int32_t      role_or_status;  /* +0x10  rw=r sz=4 */
};
```