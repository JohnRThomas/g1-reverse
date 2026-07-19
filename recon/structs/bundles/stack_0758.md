### cluster stack_0758  (stack, 1 members, 2 fields, size>=0x1c)

Stack-frame local local_1d0 in battery_model_state_update (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - battery_model_state_update @ 0xc358  as local_1d0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0758 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x14];   /* +0x4 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
};
```