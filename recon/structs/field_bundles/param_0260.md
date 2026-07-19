### struct gatt_ccc_update_ctx  (library:bt_gatt_ccc)  cid=param_0260

purpose: CCC update context passed to gatt_send_ccc_update (handle/value pairs).

This object is accessed by these functions (read their fully-named source):
  - gatt_send_ccc_update  (as param_3)  ->  recon/readable_sources/app/library/gatt_send_ccc_update.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_ccc_update_ctx {
    uint16_t     field_0x4;  /* +0x4  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=w sz=4 */   <-- NAME ME
    uint16_t     field_0xc;  /* +0xc  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```