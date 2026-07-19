### cluster stack_0939  (stack, 1 members, 2 fields, size>=0x6)

Stack-frame local local_f8 in audioStreamFileManagerHandler (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - audioStreamFileManagerHandler @ 0x2f94c  as local_f8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0939 {
    uint16_t   field_0x0;   /* +0x0  sz=2 rw=r types=idx2 */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint16_t   field_0x4;   /* +0x4  sz=2 rw=r types=idx2 */
};
```