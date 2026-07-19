### cluster stack_1552  (stack, 1 members, 2 fields, size>=0x5)

Stack-frame local local_c in dev_write_reg4 (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - dev_write_reg4 @ 0x83de6  as local_c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1552 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```