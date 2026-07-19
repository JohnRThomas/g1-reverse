### struct gatt_ccc_cfg  (library:bt_gatt_ccc_cfg)  cid=param_0246

purpose: GATT CCC (client characteristic configuration) entry passed to gatt_ccc_write_store_cb.

This object is accessed by these functions (read their fully-named source):
  - gatt_ccc_write_store_cb  (as param_3)  ->  recon/readable_sources/app/library/gatt_ccc_write_store_cb.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_ccc_cfg {
    uint16_t     value_or_flags;  /* +0x0  rw=r sz=2 */
    uint8_t      field_0x1;  /* +0x1  rw=r sz=1 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
};
```