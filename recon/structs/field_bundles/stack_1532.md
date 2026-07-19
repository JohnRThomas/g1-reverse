### struct bt_gatt_attr_read_ccc_locals  (G1-original)  cid=stack_1532

purpose: Stack-local pair of 16-bit fields (handle and CCC value) used while reading a CCC attribute in bt_gatt_attr_read_ccc.

This object is accessed by these functions (read their fully-named source):
  - bt_gatt_attr_read_ccc  (as local_12)  ->  recon/readable_sources/app/library/bt_gatt_attr_read_ccc.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_gatt_attr_read_ccc_locals {
    uint16_t     field_0x0;  /* +0x0  rw=r sz=2 */   <-- NAME ME
    uint16_t     field_0x6;  /* +0x6  rw=r sz=2 */   <-- NAME ME
};
```