### cluster param_0349  (param, 3 members, 23 fields, size>=0x58c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 1/3 members are LIBRARY-class)

members (3 shown of 3):
  - nrfx_twim_irq_handler @ 0x67600  as param_1  [APPLICATION]
  - nrfx_twim_xfer @ 0x67938  as param_1  [APPLICATION]
  - xfer_completeness_check @ 0x85316  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0349 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte */
    uint8_t    _pad_0x2[0x6];   /* +0x2 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=idx4,undefined4 */
    uint8_t    _pad_0xc[0x8];   /* +0xc pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=rw types=idx4,undefined4 */
    uint8_t    _pad_0x18[0x8];   /* +0x18 pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=rw types=idx4,undefined4 */
    uint8_t    _pad_0x24[0xe0];   /* +0x24 pad */
    uint32_t   field_0x104;   /* +0x104  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x108[0x1c];   /* +0x108 pad */
    uint32_t   field_0x124;   /* +0x124  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x128[0x20];   /* +0x128 pad */
    uint32_t   field_0x148;   /* +0x148  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14c[0x10];   /* +0x14c pad */
    uint32_t   field_0x15c;   /* +0x15c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x160;   /* +0x160  sz=4 rw=rw types=idx4,undefined4 */
    uint8_t    _pad_0x164[0x9c];   /* +0x164 pad */
    uint32_t   field_0x200;   /* +0x200  sz=4 rw=rw types=idx4,int,uint,undefined4 */
    uint8_t    _pad_0x204[0x100];   /* +0x204 pad */
    uint32_t   field_0x304;   /* +0x304  sz=4 rw=rw types=idx4,int */
    uint32_t   field_0x308;   /* +0x308  sz=4 rw=rw types=idx4,int,undefined4 */
    uint8_t    _pad_0x30c[0x1b8];   /* +0x30c pad */
    uint32_t   field_0x4c4;   /* +0x4c4  sz=4 rw=rw types=idx4,int */
    uint8_t    _pad_0x4c8[0x38];   /* +0x4c8 pad */
    uint32_t   field_0x500;   /* +0x500  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x504[0x30];   /* +0x504 pad */
    uint32_t   field_0x534;   /* +0x534  sz=4 rw=r types=idx4 */
    uint32_t   field_0x538;   /* +0x538  sz=4 rw=r types=idx4 */
    uint32_t   field_0x53c;   /* +0x53c  sz=4 rw=r types=int */
    uint32_t   field_0x540;   /* +0x540  sz=4 rw=r types=idx4 */
    uint32_t   field_0x544;   /* +0x544  sz=4 rw=r types=idx4 */
    uint32_t   field_0x548;   /* +0x548  sz=4 rw=r types=idx4 */
    uint32_t   field_0x54c;   /* +0x54c  sz=4 rw=r types=int */
    uint32_t   field_0x550;   /* +0x550  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x554[0x34];   /* +0x554 pad */
    uint32_t   field_0x588;   /* +0x588  sz=4 rw=r types=idx4 */
};
```