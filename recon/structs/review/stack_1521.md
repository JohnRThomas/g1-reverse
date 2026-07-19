## review group stack_1521  (1 cluster(s), kinds=stack)

### proposal for stack_1521
struct_name: mpu_region_cfg | is_library: True | library_name: ARM MPU region config (arm_mpu_region_t style) | is_array: False | confidence: medium
purpose: Local ARM MPU region configuration built by mpu_configure_region: a base-address/RBAR word and, with a 4-byte gap, a limit/RLAR or attribute word.
fields:
  0x0  uint32_t     base_or_rbar  
  0x8  uint32_t     limit_or_rlar  

<ground-truth bundle for stack_1521>
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
