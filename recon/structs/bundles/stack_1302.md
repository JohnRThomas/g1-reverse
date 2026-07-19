### cluster stack_1302  (stack, 1 members, 2 fields, size>=0x6)

Stack-frame local local_19 in gpiote_trigger_enable (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - gpiote_trigger_enable @ 0x657e4  as local_19  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1302 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x4];   /* +0x1 pad */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=r types=idx1 */
};
```