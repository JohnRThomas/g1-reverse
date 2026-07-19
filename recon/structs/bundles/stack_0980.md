### cluster stack_0980  (stack, 1 members, 4 fields, size>=0x10)

Stack-frame local local_2c in render_device_info_float_screen (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - render_device_info_float_screen @ 0x361d8  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0980 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```