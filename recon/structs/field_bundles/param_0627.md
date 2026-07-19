### struct gatt_sc_ctx  (library:gatt_sc / sc_data (Zephyr BT GATT internal))  cid=param_0627

purpose: GATT Service Changed context cleared by gatt_sc_ctx_clear (two words).

This object is accessed by these functions (read their fully-named source):
  - gatt_sc_ctx_clear  (as param_1)  ->  recon/readable_sources/app/library/gatt_sc_ctx_clear.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_sc_ctx {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
};
```