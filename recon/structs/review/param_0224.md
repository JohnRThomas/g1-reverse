## review group param_0224  (1 cluster(s), kinds=param)

### proposal for param_0224
struct_name: net_buf | is_library: True | library_name: struct net_buf | is_array: None | confidence: medium
purpose: Zephyr net_buf passed into l2cap_recv; data pointer and leading bytes of the packet buffer.
fields:
  0xc  uint8_t *    data  
  0x10  uint16_t     buf_head_bytes  first bytes of __buf flexible array

<ground-truth bundle for param_0224>
### cluster param_0224  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: l2cap; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - l2cap_recv @ 0x57db0  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0224 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    void *     field_0xc;   /* +0xc  sz=4 rw=r types=int,ptr */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
};
```
