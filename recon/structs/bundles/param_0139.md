### cluster param_0139  (param, 1 members, 2 fields, size>=0x1b0)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_0004cce0 @ 0x4cce0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0139 {
    uint8_t    _pad_0x0[0x1a8];   /* +0x0 pad */
    void *     field_0x1a8;   /* +0x1a8  sz=4 rw=r types=ptr */
    uint32_t   field_0x1ac;   /* +0x1ac  sz=4 rw=r types=undefined4 */
};
```