### cluster stack_1044  (stack, 1 members, 2 fields, size>=0x10)

Stack-frame local local_24 in ui_refalsh_warp (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - ui_refalsh_warp @ 0x48b5c  as local_24  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1044 {
    uint8_t    _pad_0x0[0xe];   /* +0x0 pad */
    uint8_t    field_0xe;   /* +0xe  sz=1 rw=r types=char */
    uint8_t    field_0xf;   /* +0xf  sz=1 rw=r types=char */
};
```