### struct bt_att_read_group_data  (library:bt_att read-type/group iterator (host att.c internal))  cid=param_0228

purpose: ATT Read-By-Type/Group iteration context shared by read_group_cb and att_read_type_iter_cb during ATT response building.

This object is accessed by these functions (read their fully-named source):
  - read_group_cb  (as param_3)  [no source file]
  - att_read_type_iter_cb  (as param_3)  ->  recon/readable_sources/app/library/att_read_type_iter_cb.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_att_read_group_data {
    uint8_t      field_0x0;  /* +0x0  rw=r sz=1 */   <-- NAME ME
    uint32_t     field_0x4;  /* +0x4  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x5;  /* +0x5  rw=w sz=1 */   <-- NAME ME
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x10;  /* +0x10  rw=r sz=4 */   <-- NAME ME
};
```