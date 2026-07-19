### cluster param_0501  (param, 2 members, 3 fields, size>=0x28)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - free_space @ 0x7e314  as param_1  [APPLICATION]
  - get_usage @ 0x7e33a  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0501 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4,int */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14[0x10];   /* +0x14 pad */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4,int */
};
```