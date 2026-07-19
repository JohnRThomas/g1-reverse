### struct bt_gatt_subscribe_params  (library:struct bt_gatt_subscribe_params)  cid=param_0263

purpose: Zephyr GATT subscription parameters used by gatt_subscribe_add / bt_gatt_unsubscribe / gatt_mult_notify_dispatch.

This object is accessed by these functions (read their fully-named source):
  - gatt_subscribe_add  (as param_1)  ->  recon/readable_sources/app/library/gatt_subscribe_add.c
  - bt_gatt_unsubscribe  (as param_1)  ->  recon/readable_sources/app/library/bt_gatt_unsubscribe.c
  - gatt_mult_notify_dispatch  (as param_1)  ->  recon/readable_sources/app/library/gatt_mult_notify_dispatch.c
  - FUN_00082e62  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_gatt_subscribe_params {
    uint8_t      field_0x8;  /* +0x8  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x9;  /* +0x9  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0xd;  /* +0xd  rw=r sz=1 */   <-- NAME ME
};
```