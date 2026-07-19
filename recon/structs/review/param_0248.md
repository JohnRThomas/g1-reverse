## review group param_0248  (1 cluster(s), kinds=param)

### proposal for param_0248
struct_name: bt_conn | is_library: True | library_name: bt_conn | is_array: None | confidence: high
purpose: Zephyr Bluetooth connection object shared across GATT service-change, CCC write, indicate/notify, and library bt_conn_* functions
fields:
  0x3  uint8_t      field_0x3  char
  0x8  uint8_t      field_0x8  byte/undefined1
  0xb  uint8_t      field_0xb  char
  0xd  uint8_t      field_0xd  char
  0xc0  int32_t      field_0xc0  int

<ground-truth bundle for param_0248>
### cluster param_0248  (param, 9 members, 5 fields, size>=0xc4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt,gatt; 3/9 members are LIBRARY-class)

members (9 shown of 9):
  - sc_clear @ 0x5a090  as param_1  [APPLICATION]
  - gatt_remove_peer_from_attr @ 0x5a3c4  as param_3  [APPLICATION]
  - gatt_ccc_write @ 0x5a464  as param_1  [APPLICATION]
  - gatt_find_ccc_for_conn @ 0x5b0dc  as param_1  [APPLICATION]
  - bt_gatt_indicate @ 0x5b378  as param_1  [APPLICATION]
  - bt_gatt_notify_cb @ 0x5b754  as param_1  [APPLICATION]
  - bt_conn_ltk_present @ 0x8145c  as param_1  [LIBRARY]
  - bt_conn_is_peer_addr_le @ 0x814e6  as param_1  [LIBRARY]
  - bt_gatt_check_perm @ 0x82cba  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0248 {
    uint8_t    _pad_0x0[0x3];   /* +0x0 pad */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=r types=char */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=byte,undefined1 */
    uint8_t    _pad_0x9[0x2];   /* +0x9 pad */
    uint8_t    field_0xb;   /* +0xb  sz=1 rw=r types=char */
    uint8_t    _pad_0xc[0x1];   /* +0xc pad */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=r types=char */
    uint8_t    _pad_0xe[0xb2];   /* +0xe pad */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=r types=int */
};
```
