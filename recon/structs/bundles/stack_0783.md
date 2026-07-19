### cluster stack_0783  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_3c in fuel_gauge_update (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - fuel_gauge_update @ 0x10b18  as local_3c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0783 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```