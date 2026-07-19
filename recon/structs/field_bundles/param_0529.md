### struct bt_gatt_discover_params  (library:struct bt_gatt_discover_params)  cid=param_0529

purpose: Zephyr GATT discovery parameters/context whose error path is handled by discovery_complete_error.

This object is accessed by these functions (read their fully-named source):
  - discovery_complete_error  (as param_1)  ->  recon/readable_sources/app/g1/discovery_complete_error.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_gatt_discover_params {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x15c;  /* +0x15c  rw=r sz=4 */   <-- NAME ME
};
```