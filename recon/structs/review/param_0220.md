## review group param_0220  (1 cluster(s), kinds=param)

### proposal for param_0220
struct_name: bt_att_l2cap_frag_ctx | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Shared fragmentation/buffer context used by both the L2CAP LE segment-send path and the ATT data-fragment-send path in G1's Bluetooth host reimplementation.
fields:
  0x4  uint32_t     total_len  
  0x9  uint16_t     mtu_or_flags  
  0x10  uint32_t     data_ptr_or_len  
  0x26  uint16_t     remaining_len  

<ground-truth bundle for param_0220>
### cluster param_0220  (param, 2 members, 5 fields, size>=0x2a)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att,l2cap; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - l2cap_chan_le_send_seg @ 0x5757c  as param_1  [APPLICATION]
  - att_send_data_frags @ 0x81852  as param_1  [APPLICATION]

layout notes: 0x9: access width 2 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0220 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x1];   /* +0x8 pad */
    uint8_t    field_0x9;   /* +0x9  sz=2 rw=r types=undefined2 */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=r types=ushort */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14[0x12];   /* +0x14 pad */
    uint16_t   field_0x26;   /* +0x26  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x28[0x2];   /* +0x28 pad */
};
```
