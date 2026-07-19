## review group param_0221  (1 cluster(s), kinds=param)

### proposal for param_0221
struct_name: bt_conn_or_l2cap_chan | is_library: True | library_name: Zephyr Bluetooth: struct bt_conn (possibly merged with struct bt_l2cap_chan) | is_array: None | confidence: low
purpose: Large Bluetooth connection/channel object shared across l2cap_chan_send_disconnect, l2cap_chan_le_recv_seg, l2cap_le_recv_pdu, gatt_notify_send and gatt_send_service_changed_ind; most likely Zephyr's struct bt_conn, though the merge across L2CAP-channel and GATT/connection call sites (with reported field overlaps) suggests this cluster may conflate bt_conn and bt_l2cap_chan due to imprecise pointer-type unification.
fields:
  0x4  uint32_t     field_0x4  idx4/int, possibly ref count or index
  0x14  uint32_t     handle_or_state  overlapping access, possibly conn handle
  0x18  uint16_t     field_0x18  short
  0x1c  uint32_t     field_0x1c  undefined4
  0x21  uint16_t     att_mtu  write-only short, likely ATT MTU
  0x24  uint32_t     err_or_id  idx4
  0x2d  uint8_t      flags_a  rw byte
  0x2e  uint8_t      flags_b  write-only byte
  0x4c  uint32_t     field_0x4c  idx4
  0x80  uint32_t     channels_or_state  rw idx4/int
  0x84  uint16_t     mtu  rw short
  0xb4  uint8_t      field_0xb4  read-only byte
  0xb6  uint16_t     psm_or_cid  read-only short
  0xb8  uint8_t      field_0xb8  write-only byte

<ground-truth bundle for param_0221>
### cluster param_0221  (param, 5 members, 16 fields, size>=0xbc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt,l2cap; 0/5 members are LIBRARY-class)

members (5 shown of 5):
  - l2cap_chan_send_disconnect @ 0x5774c  as param_1  [APPLICATION]
  - l2cap_chan_le_recv_seg @ 0x57a04  as param_1  [APPLICATION]
  - l2cap_le_recv_pdu @ 0x57b60  as param_1  [APPLICATION]
  - gatt_notify_send @ 0x8199a  as param_1  [APPLICATION]
  - gatt_send_service_changed_ind @ 0x81b30  as param_1  [APPLICATION]

layout notes: 0x4: access width 4 exceeds gap 1 to next field (overlap/union); 0x14: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0221 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4;   /* +0x4  sz=4 rw=r types=idx4,int */
    uint16_t   field_0x5;   /* +0x5  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x7[0xd];   /* +0x7 pad */
    uint16_t   field_0x14;   /* +0x14  sz=2,4 rw=r types=idx4,undefined2 */
    uint16_t   field_0x16;   /* +0x16  sz=2 rw=r types=undefined2,ushort */
    uint16_t   field_0x18;   /* +0x18  sz=2 rw=r types=undefined2,ushort */
    uint8_t    _pad_0x1a[0x2];   /* +0x1a pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x20[0x1];   /* +0x20 pad */
    uint16_t   field_0x21;   /* +0x21  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x23[0x1];   /* +0x23 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x28[0x5];   /* +0x28 pad */
    uint8_t    field_0x2d;   /* +0x2d  sz=1 rw=rw types=char,undefined1 */
    uint8_t    field_0x2e;   /* +0x2e  sz=1 rw=w types=char */
    uint8_t    _pad_0x2f[0x1d];   /* +0x2f pad */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x50[0x30];   /* +0x50 pad */
    uint32_t   field_0x80;   /* +0x80  sz=4 rw=rw types=idx4,int,undefined4 */
    uint16_t   field_0x84;   /* +0x84  sz=2 rw=rw types=short,undefined2,ushort */
    uint8_t    _pad_0x86[0x2e];   /* +0x86 pad */
    uint8_t    field_0xb4;   /* +0xb4  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0xb5[0x1];   /* +0xb5 pad */
    uint16_t   field_0xb6;   /* +0xb6  sz=2 rw=r types=undefined2 */
    uint8_t    field_0xb8;   /* +0xb8  sz=1 rw=w types=char */
    uint8_t    _pad_0xb9[0x3];   /* +0xb9 pad */
};
```
