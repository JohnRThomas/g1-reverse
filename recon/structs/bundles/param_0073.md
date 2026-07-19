### cluster param_0073  (param, 1 members, 2 fields, size>=0x38)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - orientation_get_heading_deg @ 0x26828  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0073 {
    uint8_t    _pad_0x0[0x28];   /* +0x0 pad */
    uint8_t    field_0x28;   /* +0x28  sz=1 rw=r types=char */
    uint8_t    _pad_0x29[0xb];   /* +0x29 pad */
    float      field_0x34;   /* +0x34  sz=4 rw=r types=float */
};
```