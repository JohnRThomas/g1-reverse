### cluster param_0272  (param, 1 members, 2 fields, size>=0xc4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_alloc_pairing_keys @ 0x5e47c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0272 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0x9[0xb7];   /* +0x9 pad */
    uint32_t   field_0xc0;   /* +0xc0  sz=4 rw=rw types=int,undefined4 */
};
```