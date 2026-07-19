### struct ancs_notif_ctx  (G1-original)  cid=param_0157

purpose: ANCS (Apple Notification Center Service) GATT client context shared by ancs_gatt_dm_assign_handles / ancs_subscribe_notification_source / ancs_subscribe_data_source: GATT handle shorts plus subscribe-param blocks.

This object is accessed by these functions (read their fully-named source):
  - ancs_gatt_dm_assign_handles  (as param_2)  ->  recon/readable_sources/app/g1/ancs_gatt_dm_assign_handles.c
  - ancs_subscribe_notification_source  (as param_1)  ->  recon/readable_sources/app/g1/ancs_subscribe_notification_source.c
  - ancs_subscribe_data_source  (as param_1)  ->  recon/readable_sources/app/g1/ancs_subscribe_data_source.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct ancs_notif_ctx {
    uint16_t     field_0x2;  /* +0x2  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=rw sz=2,4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x20d;  /* +0x20d  rw=w sz=2 */   <-- NAME ME
    uint16_t     field_0x215;  /* +0x215  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0x828;  /* +0x828  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x836;  /* +0x836  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0x83c;  /* +0x83c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x844;  /* +0x844  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x848;  /* +0x848  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x856;  /* +0x856  rw=w sz=2 */   <-- NAME ME
    uint32_t     field_0x85c;  /* +0x85c  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x864;  /* +0x864  rw=r sz=4 */   <-- NAME ME
};
```