### struct bt_conn_info  (library:bt_conn_info)  cid=param_0213

purpose: Zephyr bt_conn_info populated by bt_conn_get_info describing connection type/role and LE parameters.

This object is accessed by these functions (read their fully-named source):
  - bt_conn_get_info  (as param_2)  ->  recon/readable_sources/app/library/bt_conn_get_info.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_conn_info {
    uint32_t     role_or_type;  /* +0x4  rw=r sz=4 */
    uint32_t     field_0x8;  /* +0x8  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x90;  /* +0x90  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x94;  /* +0x94  rw=r sz=4 */   <-- NAME ME
    uint32_t     field_0x9c;  /* +0x9c  rw=r sz=4 */   <-- NAME ME
};
```