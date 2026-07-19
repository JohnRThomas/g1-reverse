## review group param_0166  (1 cluster(s), kinds=param)

### proposal for param_0166
struct_name: z_arch_esf_regs | is_library: True | library_name: struct arch_esf (Zephyr, offset shifted +0x4 vs canonical due to leading field) | is_array: None | confidence: medium
purpose: ARM Cortex-M33 exception stack frame (arch_esf) dumped by arm_fault_dump_esf_registers/z_fatal_error: r0-r3, r12, lr, pc plus a trailing extra field.
fields:
  0x4  uint32_t     r0  
  0x8  uint32_t     r1  
  0xc  uint32_t     r2  
  0x10  uint32_t     r3  
  0x14  uint32_t     r12  
  0x18  uint32_t     lr  
  0x1c  uint32_t     pc  
  0x60  uint32_t     field_0x60_extra  

<ground-truth bundle for param_0166>
### cluster param_0166  (param, 2 members, 8 fields, size>=0x64)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: z; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - arm_fault_dump_esf_registers @ 0x4ff6c  as param_2  [APPLICATION]
  - z_fatal_error @ 0x71684  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0166 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4,uint */
    uint8_t    _pad_0x20[0x40];   /* +0x20 pad */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=r types=idx4 */
};
```
