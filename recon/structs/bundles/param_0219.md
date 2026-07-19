### cluster param_0219  (param, 1 members, 3 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: l2cap; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - l2cap_chan_tx_init @ 0x574ec  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0219 {
    uint8_t    _pad_0x0[0x24];   /* +0x0 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=rw types=undefined4 */
};
```