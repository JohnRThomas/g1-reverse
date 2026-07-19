### cluster param_0218  (param, 1 members, 4 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: l2cap; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - l2cap_chan_rx_init @ 0x57484  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0218 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint8_t    _pad_0x8[0xe];   /* +0x8 pad */
    uint16_t   field_0x16;   /* +0x16  sz=2 rw=rw types=short,undefined2,ushort */
    uint16_t   field_0x18;   /* +0x18  sz=2 rw=rw types=short */
    uint8_t    _pad_0x1a[0x2];   /* +0x1a pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=w types=undefined4 */
};
```