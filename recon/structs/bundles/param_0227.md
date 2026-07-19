### cluster param_0227  (param, 1 members, 4 fields, size>=0x14c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_att_chan_create_pdu @ 0x585f0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0227 {
    uint8_t    _pad_0x0[0x1e];   /* +0x0 pad */
    uint16_t   field_0x1e;   /* +0x1e  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x20[0xe];   /* +0x20 pad */
    uint16_t   field_0x2e;   /* +0x2e  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x30[0x114];   /* +0x30 pad */
    uint32_t   field_0x144;   /* +0x144  sz=4 rw=r types=int */
    uint32_t   field_0x148;   /* +0x148  sz=4 rw=r types=int */
};
```