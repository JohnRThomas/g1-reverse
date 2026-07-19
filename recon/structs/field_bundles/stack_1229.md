### struct gatt_discover_locals  (G1-original)  cid=stack_1229

purpose: Local scratch in bt_gatt_discover holding two byte fields (state/type).

This object is accessed by these functions (read their fully-named source):
  - bt_gatt_discover  (as local_24)  ->  recon/readable_sources/app/library/bt_gatt_discover.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_discover_locals {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint8_t      field_0x2;  /* +0x2  rw=r sz=1 */   <-- NAME ME
};
```