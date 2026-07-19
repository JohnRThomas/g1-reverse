### cluster param_0545  (param, 1 members, 11 fields, size>=0x13)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - add_round_key @ 0x7feda  as param_2  [LIBRARY]

layout notes: overlap at 0x3 (prev field ends 0x4); overlap at 0x6 (prev field ends 0x8); overlap at 0x7 (prev field ends 0x8); overlap at 0xa (prev field ends 0xc); overlap at 0xb (prev field ends 0xc); overlap at 0xe (prev field ends 0x10); overlap at 0xf (prev field ends 0x10)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0545 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=undefined2 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x3];   /* +0x10 pad */
};
```