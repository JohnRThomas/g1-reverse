### cluster param_0347  (param, 2 members, 5 fields, size>=0x13)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - twim_configure @ 0x675c0  as param_2  [LIBRARY]
  - nrfx_twim_init @ 0x67794  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0347 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x1];   /* +0xc pad */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=r types=undefined1 */
    uint8_t    field_0xe;   /* +0xe  sz=1 rw=r types=char */
    uint8_t    field_0xf;   /* +0xf  sz=1 rw=r types=char */
    uint8_t    _pad_0x10[0x3];   /* +0x10 pad */
};
```