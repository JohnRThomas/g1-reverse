### struct gatt_subscribe_ctx  (G1-original)  cid=param_0160

purpose: G1 reimplementation of a GATT subscription context (value/CCC handles, callback/conn pointers), shared between gatt_subscribe_service_changed and gatt_service_changed_c_discovery_completed.

This object is accessed by these functions (read their fully-named source):
  - gatt_subscribe_service_changed  (as param_1)  ->  recon/readable_sources/app/library/gatt_subscribe_service_changed.c
  - gatt_service_changed_c_discovery_completed  (as param_2)  ->  recon/readable_sources/app/library/gatt_service_changed_c_discovery_completed.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_subscribe_ctx {
    uint16_t     subscribe_flags;  /* +0x1  rw=w sz=2 */
    uint16_t     value_handle;  /* +0x4  rw=r sz=4 */
    uint16_t     field_0x6;  /* +0x6  rw=w sz=2 */   <-- NAME ME
    uint32_t     ccc_handle;  /* +0x8  rw=r sz=4 */
    uint32_t     notify_cb;  /* +0x14  rw=r sz=4 */
    uint32_t     conn_ptr;  /* +0x1c  rw=r sz=4 */
    uint32_t     field_0x24;  /* +0x24  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x28;  /* +0x28  rw=r sz=4 */   <-- NAME ME
};
```