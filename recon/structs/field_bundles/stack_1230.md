### struct bt_gatt_discover_tmp  (library:bt_gatt_discover local scratch)  cid=stack_1230

purpose: Stack local (local_20) in bt_gatt_discover: small parameter/state bytes for the discovery request.

This object is accessed by these functions (read their fully-named source):
  - bt_gatt_discover  (as local_20)  ->  recon/readable_sources/app/library/bt_gatt_discover.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_gatt_discover_tmp {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
};
```