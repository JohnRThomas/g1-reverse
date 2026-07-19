## review group param_0229  (1 cluster(s), kinds=param)

### proposal for param_0229
struct_name: bt_att_chan | is_library: True | library_name: bt_att_chan (approx bt_l2cap_le_chan-derived) | is_array: None | confidence: low
purpose: Bluetooth ATT channel context used by att_chan_send/chan_req_send to track MTU/CID and pending-request bookkeeping.
fields:
  0x1e  uint16_t     mtu_or_cid_a  read-only ushort
  0x2e  uint16_t     mtu_or_cid_b  read-only ushort
  0x120  uint32_t     req_state  read-only idx4
  0x124  uint32_t     req_extra  write-only word

<ground-truth bundle for param_0229>
### cluster param_0229  (param, 2 members, 4 fields, size>=0x128)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - att_chan_send @ 0x58a54  as param_1  [APPLICATION]
  - chan_req_send @ 0x82030  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0229 {
    uint8_t    _pad_0x0[0x1e];   /* +0x0 pad */
    uint16_t   field_0x1e;   /* +0x1e  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x20[0xe];   /* +0x20 pad */
    uint16_t   field_0x2e;   /* +0x2e  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x30[0xf0];   /* +0x30 pad */
    uint32_t   field_0x120;   /* +0x120  sz=4 rw=r types=idx4 */
    uint32_t   field_0x124;   /* +0x124  sz=4 rw=w types=int,undefined4 */
};
```
