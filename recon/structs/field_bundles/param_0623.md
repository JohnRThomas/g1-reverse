### struct gatt_find_info_entry  (library:bt att/gatt find-info (unresolved))  cid=param_0623

purpose: ATT Find-Information response encoding context (attribute handle / UUID 16-bit fields) used by gatt_find_info_encode.

This object is accessed by these functions (read their fully-named source):
  - gatt_find_info_encode  (as param_3)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct gatt_find_info_entry {
    uint16_t     field_0x8;  /* +0x8  rw=r sz=2 */   <-- NAME ME
    uint16_t     field_0xe;  /* +0xe  rw=r sz=2 */   <-- NAME ME
};
```