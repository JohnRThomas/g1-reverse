### cluster param_0222  (param, 1 members, 6 fields, size>=0x31)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: l2cap; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - l2cap_chan_add @ 0x57874  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0222 {
    uint8_t    _pad_0x0[0x5];   /* +0x0 pad */
    uint16_t   field_0x5;   /* +0x5  sz=2 rw=w types=short */
    uint8_t    _pad_0x7[0x1];   /* +0x7 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x15];   /* +0x18 pad */
    uint8_t    field_0x2d;   /* +0x2d  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x2e[0x3];   /* +0x2e pad */
};
```