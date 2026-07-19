### cluster stack_0785  (stack, 1 members, 4 fields, size>=0x1a)

Stack-frame local local_44 in z_cbvprintf_impl (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: z; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - z_cbvprintf_impl @ 0x113a8  as local_44  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0785 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=idx1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x3[0x16];   /* +0x3 pad */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=r types=idx1 */
};
```