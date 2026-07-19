### cluster param_0343  (param, 1 members, 13 fields, size>=0x27)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_spim_configure @ 0x66ec0  as param_2  [APPLICATION]

layout notes: overlap at 0x6 (prev field ends 0x8); overlap at 0x9 (prev field ends 0xc)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0343 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=1,4 rw=r types=byte,idx4,undefined1 */
    uint32_t   field_0x8;   /* +0x8  sz=1,4 rw=r types=byte,idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x2];   /* +0x10 pad */
    uint8_t    field_0x12;   /* +0x12  sz=1 rw=r types=byte */
    uint8_t    _pad_0x13[0x1];   /* +0x13 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x1];   /* +0x18 pad */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=r types=byte */
    uint8_t    field_0x1a;   /* +0x1a  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0x1b[0x1];   /* +0x1b pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x20[0x1];   /* +0x20 pad */
    uint8_t    field_0x21;   /* +0x21  sz=1 rw=r types=char */
    uint8_t    field_0x22;   /* +0x22  sz=1 rw=r types=byte */
    uint8_t    field_0x23;   /* +0x23  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0x24[0x3];   /* +0x24 pad */
};
```