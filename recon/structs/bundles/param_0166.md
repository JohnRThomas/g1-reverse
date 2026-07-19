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