### cluster param_0106  (param, 1 members, 2 fields, size>=0x1d)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - draw_message @ 0x35afc  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0106 {
    uint8_t    _pad_0x0[0x14];   /* +0x0 pad */
    uint8_t    field_0x14;   /* +0x14  sz=1 rw=r types=char */
    uint8_t    _pad_0x15[0x7];   /* +0x15 pad */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=r types=char */
};
```