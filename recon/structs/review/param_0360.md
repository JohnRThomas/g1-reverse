## review group param_0360  (1 cluster(s), kinds=param)

### proposal for param_0360
struct_name: metal_device_region | is_library: True | library_name: metal_device (libmetal) | is_array: False | confidence: low
purpose: Region/attribute block passed to metal_register_generic_device (libmetal), likely part of struct metal_device holding physmap/attribute fields.
fields:
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  
  0x24  uint32_t     field_0x24  
  0x28  uint32_t     field_0x28  

<ground-truth bundle for param_0360>
### cluster param_0360  (param, 1 members, 4 fields, size>=0x2c)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - metal_register_generic_device @ 0x68170  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0360 {
    uint8_t    _pad_0x0[0x1c];   /* +0x0 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
};
```
