### cluster param_0223  (param, 2 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: l2cap; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - l2cap_chan_le_recv_seg @ 0x57a04  as param_2  [APPLICATION]
  - l2cap_le_recv_pdu @ 0x57b60  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0223 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x10;   /* +0x10  sz=2 rw=r types=short,undefined2,ushort */
    uint8_t    _pad_0x12[0x2];   /* +0x12 pad */
};
```