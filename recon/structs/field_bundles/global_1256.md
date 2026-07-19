### struct bt_keys_pool  (library:bt_keys[] pool)  cid=global_1256

purpose: Zephyr Bluetooth bonded-keys storage pool (array of struct bt_keys) scanned by bt_keys_find_irk to resolve an IRK.

This object is accessed by these functions (read their fully-named source):
  - bt_keys_find_irk  (as 0x0005e928)  ->  recon/readable_sources/app/library/bt_keys_find_irk.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_keys_pool {
    uint16_t     field_0xe;  /* +0xe  rw=r sz=2 */   <-- NAME ME
    uint16_t     field_0x6a;  /* +0x6a  rw=r sz=2 */   <-- NAME ME
    uint32_t     field_0x170;  /* +0x170  rw=r sz=4 */   <-- NAME ME
};
```