### cluster stack_1428  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_70 in vsprintf_impl (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - vsprintf_impl @ 0x77c78  as local_70  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1428 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```