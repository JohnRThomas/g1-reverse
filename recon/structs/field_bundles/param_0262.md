### struct bt_gatt_subscribe_params  (library:bt_gatt_subscribe_params)  cid=param_0262

purpose: Zephyr GATT subscribe-parameters object used by gatt_subscribe_add/bt_gatt_unsubscribe: value/CCC handles and callback/list fields.

This object is accessed by these functions (read their fully-named source):
  - gatt_subscribe_add  (as param_2)  ->  recon/readable_sources/app/library/gatt_subscribe_add.c
  - bt_gatt_unsubscribe  (as param_2)  ->  recon/readable_sources/app/library/bt_gatt_unsubscribe.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_gatt_subscribe_params {
    uint16_t     field_0x4;  /* +0x4  rw=rw sz=2 */   <-- NAME ME
    uint16_t     value_handle;  /* +0xc  rw=r sz=4 */
    uint16_t     ccc_handle;  /* +0xe  rw=r sz=2 */
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
};
```