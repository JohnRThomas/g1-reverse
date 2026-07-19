### cluster stack_0751  (stack, 1 members, 4 fields, size>=0x5)

Stack-frame local local_258 in battery_model_state_update (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - battery_model_state_update @ 0xc358  as local_258  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0751 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=idx1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```