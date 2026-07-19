### cluster param_0170  (param, 2 members, 3 fields, size>=0xe)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - arm_core_mpu_configure @ 0x50c54  as param_1  [APPLICATION]
  - mpu_configure_region @ 0x80798  as param_2  [APPLICATION]

layout notes: 0x8: access width 4 exceeds gap 2 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0170 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint16_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0xc[0x2];   /* +0xc pad */
};
```