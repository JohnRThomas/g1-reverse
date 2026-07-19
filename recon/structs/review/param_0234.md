## review group param_0234  (1 cluster(s), kinds=param)

### proposal for param_0234
struct_name: bt_att_chan_mtu | is_library: True | library_name: bt_att_chan | is_array: None | confidence: medium
purpose: Zephyr BLE ATT channel object exposing negotiated/local MTU fields used by MTU exchange and response-PDU creation
fields:
  0x1e  uint16_t     rx_mtu  
  0x2e  uint16_t     tx_mtu  

<ground-truth bundle for param_0234>
### cluster param_0234  (param, 3 members, 2 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att,bt,gatt; 0/3 members are LIBRARY-class)

members (3 shown of 3):
  - bt_att_create_rsp_pdu @ 0x58f34  as param_1  [APPLICATION]
  - gatt_recompute_max_mtu @ 0x81c22  as param_1  [APPLICATION]
  - att_exchange_mtu_req @ 0x82396  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0234 {
    uint8_t    _pad_0x0[0x1e];   /* +0x0 pad */
    uint16_t   field_0x1e;   /* +0x1e  sz=2 rw=rw types=undefined2,ushort */
    uint8_t    _pad_0x20[0xe];   /* +0x20 pad */
    uint16_t   field_0x2e;   /* +0x2e  sz=2 rw=rw types=ushort */
};
```
