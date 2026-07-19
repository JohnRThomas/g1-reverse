### cluster stack_0848  (stack, 1 members, 3 fields, size>=0x7)

Stack-frame local local_1fa in ble_process_get_req (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - ble_process_get_req @ 0x1a064  as local_1fa  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0848 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x2[0x4];   /* +0x2 pad */
    uint8_t    field_0x6;   /* +0x6  sz=1 rw=r types=idx1 */
};
```