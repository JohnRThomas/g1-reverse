### cluster param_0311  (param, 1 members, 5 fields, size>=0xb)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - uarte_nrfx_configure @ 0x62ad8  as param_2  [LIBRARY]

layout notes: overlap at 0x5 (prev field ends 0x8); overlap at 0x6 (prev field ends 0x8); overlap at 0x7 (prev field ends 0x8)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0311 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=char */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x3];   /* +0x8 pad */
};
```