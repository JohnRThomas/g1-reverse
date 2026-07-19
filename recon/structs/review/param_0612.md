## review group param_0612  (1 cluster(s), kinds=param)

### proposal for param_0612
struct_name: bt_att_chan_view2 | is_library: True | library_name: bt_conn / bt_att_chan | is_array: None | confidence: low
purpose: BT ATT channel view read by att_write_cmd for connection state and MTU, similar shape to param_0182.
fields:
  0xc  uint32_t     conn_state  read
  0x10  uint16_t     mtu  read

<ground-truth bundle for param_0612>
### cluster param_0612  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - att_write_cmd @ 0x82258  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0612 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
};
```
