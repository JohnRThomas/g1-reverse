### cluster stack_1053  (stack, 1 members, 2 fields, size>=0x1d)

Stack-frame local local_28 in display_powerEvent (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - display_powerEvent @ 0x49a28  as local_28  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1053 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1b];   /* +0x1 pad */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=r types=idx1 */
};
```