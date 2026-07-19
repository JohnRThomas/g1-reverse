### cluster stack_0860  (stack, 1 members, 5 fields, size>=0x405)

Stack-frame local local_428 in calc_flash_crc (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - calc_flash_crc @ 0x22974  as local_428  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0860 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=idx1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x4[0x400];   /* +0x4 pad */
    uint8_t    field_0x404;   /* +0x404  sz=1 rw=r types=idx1 */
};
```