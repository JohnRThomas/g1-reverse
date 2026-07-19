### cluster stack_1380  (stack, 1 members, 2 fields, size>=0xfc)

Stack-frame local local_268 in lc3_sns_analyze (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_analyze @ 0x6c778  as local_268  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1380 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0xf4];   /* +0x4 pad */
    uint32_t   field_0xf8;   /* +0xf8  sz=4 rw=r types=idx4 */
};
```