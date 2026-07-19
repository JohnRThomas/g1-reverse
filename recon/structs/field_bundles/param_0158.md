### struct bt_ancs_client_ctx  (G1-original)  cid=param_0158

purpose: G1-original Apple Notification Center Service (ANCS) client context: handle/attribute bookkeeping fields, a large (~0x8bb-byte) attribute-data buffer, and discovery/state trailer fields; used by bt_ancs_cp_write / bt_ancs_request_attrs / bt_ancs_app_attr_request.

This object is accessed by these functions (read their fully-named source):
  - bt_ancs_cp_write  (as param_1)  ->  recon/readable_sources/app/library/bt_ancs_cp_write.c
  - bt_ancs_request_attrs  (as param_1)  [no source file]
  - bt_ancs_app_attr_request  (as param_1)  ->  recon/readable_sources/app/g1/bt_ancs_app_attr_request.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_ancs_client_ctx {
    uint16_t     field_0x2;  /* +0x2  rw=r sz=2 */   <-- NAME ME
    uint32_t     state_flags;  /* +0x4  rw=rw sz=4 */
    uint16_t     field_0x6;  /* +0x6  rw=w sz=2 */   <-- NAME ME
    uint16_t     ccc_handle;  /* +0x8  rw=w sz=2 */
    uint32_t     attr_id;  /* +0x14  rw=r sz=4 */
    uint16_t     attr_len;  /* +0x1a  rw=w sz=2 */
    uint32_t     attr_flags;  /* +0x1c  rw=r sz=4 */
    uint32_t     notif_uid;  /* +0x24  rw=r sz=4 */
    uint8_t      category_id;  /* +0x28  rw=w sz=1 */
    uint8_t      category_count;  /* +0x29  rw=w sz=1 */
    uint8_t      event_id;  /* +0x2a  rw=w sz=1 */
    uint8_t      event_flags;  /* +0x2b  rw=w sz=1 */
    uint8_t      client_state;  /* +0x2c  rw=w sz=1 */
    uint8_t      attr_buf_flag;  /* +0x8e8  rw=r sz=1 */
    uint32_t     attr_buf_len;  /* +0x8f8  rw=rw sz=4 */
    uint32_t     discover_state;  /* +0x904  rw=w sz=4 */
    uint8_t      conn_active;  /* +0x908  rw=w sz=1 */
};
```