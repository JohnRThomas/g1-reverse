### cluster param_0430  (param, 3 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - vfprintf_core @ 0x78f88  as param_2  [APPLICATION]
  - vfprintf_field_scan_match @ 0x79278  as param_3  [APPLICATION]
  - scanf_convert_integer_field @ 0x7932c  as param_3  [APPLICATION]

layout notes: overlap at 0x4 (prev field ends 0x5)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0430 {
    uint8_t    _pad_0x0[0x3];   /* +0x0 pad */
    uint16_t   field_0x3;   /* +0x3  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x5[0x3];   /* +0x5 pad */
};
```