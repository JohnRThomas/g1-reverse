### struct bt_conn  (library:bt_conn)  cid=param_0585

purpose: Zephyr Bluetooth connection object; bt_conn_enc_key_size reads an enc_key_size-style byte at 0xb and a uint at 0xc0.

This object is accessed by these functions (read their fully-named source):
  - bt_conn_enc_key_size  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct bt_conn {
    uint8_t      enc_key_size;  /* +0xb  rw=r sz=1 */
    uint32_t     field_0xc0;  /* +0xc0  rw=r sz=4 */   <-- NAME ME
};
```