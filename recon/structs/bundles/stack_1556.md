### cluster stack_1556  (stack, 1 members, 2 fields, size>=0x5)

Stack-frame local local_24 in post_event_tag2_from_node (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - post_event_tag2_from_node @ 0x8484e  as local_24  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1556 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```