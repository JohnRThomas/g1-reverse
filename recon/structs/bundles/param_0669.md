### cluster param_0669  (param, 1 members, 2 fields, size>=0xa)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - dev_write_channel_mode @ 0x843ba  as param_2  [APPLICATION]

layout notes: overlap at 0x6 (prev field ends 0x8)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0669 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x2];   /* +0x8 pad */
};
```