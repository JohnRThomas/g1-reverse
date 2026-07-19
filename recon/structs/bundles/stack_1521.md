### cluster stack_1521  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_20 in mpu_configure_region (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - mpu_configure_region @ 0x80798  as local_20  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1521 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```