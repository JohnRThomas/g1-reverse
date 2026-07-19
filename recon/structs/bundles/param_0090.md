### cluster param_0090  (param, 1 members, 2 fields, size>=0x7)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - set_brightness_lum_base @ 0x31cbc  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0090 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=char */
    uint16_t   field_0x5;   /* +0x5  sz=2 rw=r types=ushort */
};
```