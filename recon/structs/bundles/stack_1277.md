### cluster stack_1277  (stack, 1 members, 2 fields, size>=0x8)

Stack-frame local local_32 in panel_temp_calibration_init (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - panel_temp_calibration_init @ 0x62644  as local_32  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1277 {
    uint16_t   field_0x0;   /* +0x0  sz=2 rw=r types=idx2 */
    uint8_t    _pad_0x2[0x4];   /* +0x2 pad */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=r types=idx2 */
};
```