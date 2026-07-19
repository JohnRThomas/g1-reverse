### cluster param_0092  (param, 1 members, 2 fields, size>=0x6)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - set_display_brightness @ 0x32254  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0092 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=byte */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=r types=byte */
};
```