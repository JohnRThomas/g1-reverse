### cluster stack_1248  (stack, 1 members, 2 fields, size>=0x24)

Stack-frame local local_48 in smp_dhkey_check_generate (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: smp; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - smp_dhkey_check_generate @ 0x5d0ac  as local_48  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1248 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x1c];   /* +0x4 pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
};
```