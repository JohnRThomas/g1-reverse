### cluster param_0558  (param, 1 members, 2 fields, size>=0x48)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_reassembly_init @ 0x80b28  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0558 {
    uint8_t    _pad_0x0[0x40];   /* +0x0 pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=w types=undefined4 */
    uint16_t   field_0x44;   /* +0x44  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x46[0x2];   /* +0x46 pad */
};
```