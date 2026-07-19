## review group stack_1066  (1 cluster(s), kinds=stack)

### proposal for stack_1066
struct_name: log_msg_desc | is_library: True | library_name: z_log_msg2 descriptor (best-effort match) | is_array: False | confidence: low
purpose: Local descriptor in g1_recon_z_log_msg_alloc mirroring Zephyr's logging message allocation descriptor: a size/id field followed (with a gap) by a length/pointer field.
fields:
  0x0  uint32_t     field_0x0  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for stack_1066>
### cluster stack_1066  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_2c in g1_recon_z_log_msg_alloc (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - g1_recon_z_log_msg_alloc @ 0x4d55c  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1066 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
