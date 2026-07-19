### struct gatt_ccc_list_node  (library:bt_gatt internal (CCC/list node))  cid=param_0249

purpose: Internal GATT CCC/list node shared by gatt_write_ccc_rsp and list_unlink_and_release (handle + value + link fields).

This object is accessed by these functions (read their fully-named source):
  - gatt_write_ccc_rsp  (as param_5)  ->  recon/readable_sources/app/library/gatt_write_ccc_rsp.c
  - list_unlink_and_release  (as param_4)  ->  recon/readable_sources/app/g1/list_unlink_and_release.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_ccc_list_node {
    uint32_t     handle;  /* +0x4  rw=r sz=2,4 */
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
};
```