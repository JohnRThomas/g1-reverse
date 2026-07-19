## review group param_0170  (1 cluster(s), kinds=param)

### proposal for param_0170
struct_name: arm_mpu_region | is_library: True | library_name: struct arm_mpu_region (Zephyr arch/arm) / ARM_MPU_Region_t | is_array: None | confidence: medium
purpose: CMSIS/Zephyr ARM MPU region descriptor (RBAR/RASR-style base+attribute pair) used by arm_core_mpu_configure and mpu_configure_region.
fields:
  0x4  uint32_t     base_addr  RBAR-equivalent region base
  0x8  uint32_t     attr  RASR-equivalent region attributes/size

<ground-truth bundle for param_0170>
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
