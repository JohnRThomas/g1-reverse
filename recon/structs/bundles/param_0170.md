### cluster param_0170  (param, 2 members, 3 fields, size>=0xe)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - arm_core_mpu_configure @ 0x50c54  as param_1  [APPLICATION]
  - mpu_configure_region @ 0x80798  as param_2  [APPLICATION]

layout notes: overlap at 0xa (prev field ends 0xc)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0170 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x2];   /* +0xc pad */
};
```