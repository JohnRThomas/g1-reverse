## review group stack_1112  (1 cluster(s), kinds=stack)

### proposal for stack_1112
struct_name: arm_mpu_configure_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local MPU region config temporaries used when configuring the Cortex-M33 MPU
fields:
  0x0  uint32_t     field_0x0  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for stack_1112>
### cluster stack_1112  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_38 in arm_core_mpu_configure (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - arm_core_mpu_configure @ 0x50c54  as local_38  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1112 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
