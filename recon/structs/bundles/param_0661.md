### cluster param_0661  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - pinctrl_lookup_state @ 0x83eb8  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0661 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int,uint */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=byte */
    uint8_t    _pad_0x9[0x3];   /* +0x9 pad */
};
```