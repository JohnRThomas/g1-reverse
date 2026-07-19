### cluster stack_1027  (stack, 1 members, 3 fields, size>=0xc)

Stack-frame local local_2f4 in gui_utf_Wordwrap_draw (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - gui_utf_Wordwrap_draw @ 0x451e0  as local_2f4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1027 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```