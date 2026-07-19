### cluster param_0641  (param, 1 members, 2 fields, size>=0x9)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_c1 @ 0x8323a  as param_6  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0641 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint32_t   field_0x1;   /* +0x1  sz=4 rw=r types=undefined4 */
    uint16_t   field_0x5;   /* +0x5  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0x7[0x2];   /* +0x7 pad */
};
```