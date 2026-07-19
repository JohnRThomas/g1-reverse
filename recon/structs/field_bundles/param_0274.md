### struct bt_keys_irk_lookup_view  (library:bt_keys)  cid=param_0274

purpose: param_2 of bt_keys_find_irk: partial bt_keys record scanned during IRK match.

This object is accessed by these functions (read their fully-named source):
  - bt_keys_find_irk  (as param_2)  ->  recon/readable_sources/app/library/bt_keys_find_irk.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_keys_irk_lookup_view {
    uint32_t     field_0x1;  /* +0x1  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0x5;  /* +0x5  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0x18;  /* +0x18  rw=r sz=4 */   <-- NAME ME
};
```