### struct bt_ancs_client_ctx  (G1-original)  cid=param_0539

purpose: G1-original ANCS client context (>=0x8f8) passed to bt_ancs_register_app_attr: a flag byte and count/status fields in the discovery-state trailer.

This object is accessed by these functions (read their fully-named source):
  - bt_ancs_register_app_attr  (as param_1)  ->  recon/readable_sources/app/library/bt_ancs_register_app_attr.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_ancs_client_ctx {
    uint8_t      field_0x8e8;  /* +0x8e8  rw=w sz=1 */   <-- NAME ME
    uint16_t     field_0x8f0;  /* +0x8f0  rw=w sz=2 */   <-- NAME ME
    int32_t      field_0x8f4;  /* +0x8f4  rw=w sz=4 */   <-- NAME ME
};
```