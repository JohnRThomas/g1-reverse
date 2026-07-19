### struct bt_gatt_ccc_managed_user_data  (library:_bt_gatt_ccc / bt_gatt_ccc_managed_user_data)  cid=param_0618

purpose: GATT Client Characteristic Configuration state read/written by gatt_ccc_changed: a CCC value short at 0x8, a second short at 0xa, and a cfg_changed callback pointer at 0xc.

This object is accessed by these functions (read their fully-named source):
  - gatt_ccc_changed  (as param_2)  ->  recon/readable_sources/app/library/gatt_ccc_changed.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_gatt_ccc_managed_user_data {
    uint16_t     value;  /* +0x8  rw=r sz=2 */
    uint16_t     field_0xa;  /* +0xa  rw=rw sz=2 */   <-- NAME ME
    void *       cfg_changed;  /* +0xc  rw=r sz=4 */
};
```