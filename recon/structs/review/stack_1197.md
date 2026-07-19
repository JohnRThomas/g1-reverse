## review group stack_1197  (1 cluster(s), kinds=stack)

### proposal for stack_1197
struct_name: bt_att_chan_local | is_library: True | library_name: bt_l2cap_chan / bt_att_chan (best guess) | is_array: None | confidence: low
purpose: Stack-local Bluetooth channel/context object in bt_att_accept, consistent with an on-stack struct bt_l2cap_chan/bt_att_chan populated before being handed to the connection accept path.
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0x28  uint32_t     field_0x28  
  0x2c  uint32_t     field_0x2c  
  0x30  uint32_t     field_0x30  
  0x34  uint32_t     field_0x34  

<ground-truth bundle for stack_1197>
### cluster stack_1197  (stack, 1 members, 6 fields, size>=0x38)

Stack-frame local local_20 in bt_att_accept (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_att_accept @ 0x58930  as local_20  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1197 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x1c];   /* +0xc pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
};
```
