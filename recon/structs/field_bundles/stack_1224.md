### struct bt_gatt_indicate_locals  (G1-original)  cid=stack_1224

purpose: Stack-local flag bytes (local_28) in bt_gatt_indicate.

This object is accessed by these functions (read their fully-named source):
  - bt_gatt_indicate  (as local_28)  ->  recon/readable_sources/app/library/bt_gatt_indicate.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_gatt_indicate_locals {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
};
```