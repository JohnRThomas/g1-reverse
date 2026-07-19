### struct bt_uuid_32  (library:bt_uuid_32)  cid=param_0185

purpose: Zephyr Bluetooth 32-bit UUID object used by bt_uuid_expand_to_128 and bt_uuid_cmp: type byte (struct bt_uuid) followed by 32-bit val.

This object is accessed by these functions (read their fully-named source):
  - bt_uuid_expand_to_128  (as param_1)  ->  recon/readable_sources/app/g1/bt_uuid_expand_to_128.c
  - bt_uuid_cmp  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_uuid_32 {
    uint16_t     field_0x2;  /* +0x2  rw=r sz=2 */   <-- NAME ME
    uint32_t     val;  /* +0x4  rw=r sz=4 */
};
```