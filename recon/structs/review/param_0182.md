## review group param_0182  (1 cluster(s), kinds=param)

### proposal for param_0182
struct_name: bt_att_chan_view | is_library: True | library_name: bt_conn / bt_att_chan | is_array: None | confidence: low
purpose: Partial view of a BT ATT/connection channel object accessed by gatt_notify_send_chunked and att_get_max_payload_len to read negotiated MTU/state.
fields:
  0xc  int          conn_state_or_handle  read
  0x10  uint16_t     mtu  read, negotiated ATT MTU
  0x18  uint32_t     role_or_type  read
  0x1c  uint8_t      flags  read

<ground-truth bundle for param_0182>
### cluster param_0182  (param, 2 members, 4 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att,gatt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - gatt_notify_send_chunked @ 0x52880  as param_1  [APPLICATION]
  - att_get_max_payload_len @ 0x80c7c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0182 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x12[0x6];   /* +0x12 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=int,uint */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=r types=char */
    uint8_t    _pad_0x1d[0x3];   /* +0x1d pad */
};
```
