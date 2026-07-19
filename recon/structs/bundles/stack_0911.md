### cluster stack_0911  (stack, 1 members, 2 fields, size>=0x5)

Stack-frame local local_38 in opt3001_reg_read (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - opt3001_reg_read @ 0x2e594  as local_38  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0911 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```