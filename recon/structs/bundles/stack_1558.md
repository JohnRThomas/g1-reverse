### cluster stack_1558  (stack, 1 members, 2 fields, size>=0x15)

Stack-frame local local_1c in post_event_tag5 (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - post_event_tag5 @ 0x848b0  as local_1c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1558 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x13];   /* +0x1 pad */
    uint8_t    field_0x14;   /* +0x14  sz=1 rw=r types=idx1 */
};
```