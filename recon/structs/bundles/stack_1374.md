### cluster stack_1374  (stack, 1 members, 2 fields, size>=0x48)

Stack-frame local afStack_70 in lc3_ltpf_analyse (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_ltpf_analyse @ 0x6ab80  as afStack_70  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1374 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x34];   /* +0x10 pad */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
};
```