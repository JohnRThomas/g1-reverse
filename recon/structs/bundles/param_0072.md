### cluster param_0072  (param, 1 members, 2 fields, size>=0x34)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - orientation_get_pitch_deg @ 0x26808  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0072 {
    uint8_t    _pad_0x0[0x28];   /* +0x0 pad */
    uint8_t    field_0x28;   /* +0x28  sz=1 rw=r types=char */
    uint8_t    _pad_0x29[0x7];   /* +0x29 pad */
    float      field_0x30;   /* +0x30  sz=4 rw=r types=float */
};
```