### struct bt_bond_iter_scratch  (library:bt_keys)  cid=global_1253

purpose: Global scratch at 0x5e750 touched by bt_foreach_bond during bonded-device iteration (partial view of a bt_keys/bt_addr_le record).

This object is accessed by these functions (read their fully-named source):
  - bt_foreach_bond  (as 0x0005e750)  ->  recon/readable_sources/app/library/bt_foreach_bond.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_bond_iter_scratch {
    uint32_t     field_0x1;  /* +0x1  rw=r sz=4 */   <-- NAME ME
    uint16_t     field_0xe;  /* +0xe  rw=r sz=2 */   <-- NAME ME
};
```