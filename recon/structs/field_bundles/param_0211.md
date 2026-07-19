### struct ble_conn_le_alloc_param  (G1-original)  cid=param_0211

purpose: G1-original LE connection-allocation parameter block used by ble_conn_le_alloc (interval/handle field plus a role/state byte).

This object is accessed by these functions (read their fully-named source):
  - ble_conn_le_alloc  (as param_2)  ->  recon/readable_sources/app/g1/ble_conn_le_alloc.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ble_conn_le_alloc_param {
    uint16_t     field_0x1;  /* +0x1  rw=r sz=2 */   <-- NAME ME
    uint8_t      field_0x6;  /* +0x6  rw=r sz=1 */   <-- NAME ME
};
```