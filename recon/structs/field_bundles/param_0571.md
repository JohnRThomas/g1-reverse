### struct bt_conn  (library:bt_conn)  cid=param_0571

purpose: Zephyr bt_conn: security-level fields updated by update_sec_level (sec_level byte + required byte + a word at 0xc0).

This object is accessed by these functions (read their fully-named source):
  - update_sec_level  (as param_1)  ->  recon/readable_sources/app/library/update_sec_level.c

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_conn {
    uint8_t      sec_level;  /* +0x9  rw=w sz=1 */
    uint8_t      required_sec_level;  /* +0xa  rw=r sz=1 */
    int32_t      field_0xc0;  /* +0xc0  rw=r sz=4 */   <-- NAME ME
};
```