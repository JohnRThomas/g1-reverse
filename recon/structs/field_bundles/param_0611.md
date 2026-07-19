### struct bt_gatt_indicate_params  (library:bt_gatt_indicate_params)  cid=param_0611

purpose: ATT indicate parameters passed to att_indicate (value word + attribute handle).

This object is accessed by these functions (read their fully-named source):
  - att_indicate  (as param_2)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_gatt_indicate_params {
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint16_t     handle;  /* +0x10  rw=r sz=2 */
};
```