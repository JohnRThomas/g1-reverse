### cluster stack_0960  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_1c in process_pt_data (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - process_pt_data @ 0x330ec  as local_1c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0960 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```