## review group stack_1191  (1 cluster(s), kinds=stack)

### proposal for stack_1191
struct_name: l2cap_le_chan_init_locals | is_library: True | library_name: Zephyr Bluetooth: struct bt_l2cap_le_chan (stack-local init values) | is_array: None | confidence: low
purpose: Local L2CAP LE channel setup parameters in bt_l2cap_connected: channel pointer, MTU/state word and two 16-bit fields (psm/cid or credits).
fields:
  0x4  void *       chan  read-only pointer, l2cap channel
  0x10  uint32_t     mtu  rw uint
  0x14  uint16_t     field_0x14  write-only short
  0x24  uint16_t     field_0x24  write-only short

<ground-truth bundle for stack_1191>
### cluster stack_1191  (stack, 1 members, 4 fields, size>=0x28)

Stack-frame local local_14 in bt_l2cap_connected (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_l2cap_connected @ 0x5791c  as local_14  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1191 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=int,ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=uint */
    uint16_t   field_0x14;   /* +0x14  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x16[0xe];   /* +0x16 pad */
    uint16_t   field_0x24;   /* +0x24  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x26[0x2];   /* +0x26 pad */
};
```
