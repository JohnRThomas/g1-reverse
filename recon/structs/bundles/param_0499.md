### cluster param_0499  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - _ldiv5 @ 0x7e260  as param_1  [APPLICATION]

layout notes: 0x0: access width 8 exceeds gap 4 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0499 {
    uint32_t   field_0x0;   /* +0x0  sz=8 rw=w types=ulonglong */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x4];   /* +0x8 pad */
};
```