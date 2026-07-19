### cluster stack_1207  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_30 in FUN_00059344 (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - FUN_00059344 @ 0x59344  as local_30  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1207 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```