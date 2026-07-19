### cluster param_0348  (param, 2 members, 2 fields, size>=0x5)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - twim_configure @ 0x675c0  as param_1  [LIBRARY]
  - nrfx_twim_init @ 0x67794  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0348 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=byte */
};
```