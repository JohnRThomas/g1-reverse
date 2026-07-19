### cluster stack_1533  (stack, 1 members, 2 fields, size>=0x9)

Stack-frame local local_14 in cf_read (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - cf_read @ 0x829c0  as local_14  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1533 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x7];   /* +0x1 pad */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=idx1 */
};
```