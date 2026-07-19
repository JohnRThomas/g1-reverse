### struct bt_att_find_type_req  (library:bt_att_find_type_req)  cid=param_0241

purpose: Zephyr ATT Find-By-Type-Value request PDU fields parsed by att_find_type_req.

This object is accessed by these functions (read their fully-named source):
  - att_find_type_req  (as param_2)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_att_find_type_req {
    uint32_t     field_0xc;  /* +0xc  rw=r sz=4 */   <-- NAME ME
    uint8_t      field_0x10;  /* +0x10  rw=r sz=1 */   <-- NAME ME
};
```