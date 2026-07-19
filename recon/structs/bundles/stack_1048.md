### cluster stack_1048  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_40 in display_thread_handler (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - display_thread_handler @ 0x49090  as local_40  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1048 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```