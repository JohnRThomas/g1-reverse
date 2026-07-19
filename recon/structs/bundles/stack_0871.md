### cluster stack_0871  (stack, 1 members, 2 fields, size>=0x11)

Stack-frame local local_7f in read_sys_settting_from_flash (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - read_sys_settting_from_flash @ 0x232f8  as local_7f  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0871 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0xf];   /* +0x1 pad */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=idx1 */
};
```