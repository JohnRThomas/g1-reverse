### cluster param_0350  (param, 2 members, 11 fields, size>=0x29)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - nrfx_twim_irq_handler @ 0x67600  as param_2  [APPLICATION]
  - xfer_completeness_check @ 0x85316  as param_2  [LIBRARY]

layout notes: 0x8: access width 4 exceeds gap 1 to next field (overlap/union); 0x20: access width 4 exceeds gap 3 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0350 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    field_0x8;   /* +0x8  sz=4 rw=r types=idx4,int */
    uint8_t    field_0x9;   /* +0x9  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0xa[0x2];   /* +0xa pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4,int */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4,int */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint8_t    field_0x20[0x3];   /* +0x20 pad */
    uint8_t    field_0x23;   /* +0x23  sz=1 rw=rw types=byte,char,undefined1 */
    uint8_t    _pad_0x24[0x1];   /* +0x24 pad */
    uint8_t    field_0x25;   /* +0x25  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0x26[0x3];   /* +0x26 pad */
};
```