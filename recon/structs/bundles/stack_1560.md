### cluster stack_1560  (stack, 1 members, 4 fields, size>=0x10)

Stack-frame local auStack_28 in flash_write_padded_entry (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - flash_write_padded_entry @ 0x84dea  as auStack_28  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1560 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```