### struct bt_gatt_dm_attr_ctx  (library:bt_gatt_dm attribute context)  cid=param_0155

purpose: GATT discovery-manager attribute-add context (bt_gatt_dm) used by gatt_dm_data_add_attribute / discovery_callback.

This object is accessed by these functions (read their fully-named source):
  - gatt_dm_data_add_attribute  (as param_1)  ->  recon/readable_sources/app/library/gatt_dm_data_add_attribute.c
  - discovery_callback  (as param_2)  ->  recon/readable_sources/app/g1/discovery_callback.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_gatt_dm_attr_ctx {
    uint16_t     field_0x4;  /* +0x4  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x12;  /* +0x12  rw=r sz=2 */   <-- NAME ME
};
```