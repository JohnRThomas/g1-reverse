### cluster param_0606  (param, 1 members, 3 fields, size>=0x32)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: att; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - att_chan_read @ 0x81e2a  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0606 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0xc[0x12];   /* +0xc pad */
    uint16_t   field_0x1e;   /* +0x1e  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x20[0xe];   /* +0x20 pad */
    uint16_t   field_0x2e;   /* +0x2e  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x30[0x2];   /* +0x30 pad */
};
```