### struct bt_start_init_table  (G1-original)  cid=global_0840

purpose: Small 4-word table at fixed addr 0x19650 read (index/idx4) by bt_start(); a BT controller init parameter/index table.

This object is accessed by these functions (read their fully-named source):
  - bt_start  (as 0x00019650)  ->  recon/readable_sources/app/library/bt_start.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_start_init_table {
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```