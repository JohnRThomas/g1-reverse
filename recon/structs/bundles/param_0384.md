### cluster param_0384  (param, 1 members, 7 fields, size>=0x1d)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_sns_analyze @ 0x6c778  as param_5  [APPLICATION]

layout notes: overlap at 0x6 (prev field ends 0x8)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0384 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x1];   /* +0x18 pad */
    uint8_t    field_0x19;   /* +0x19  sz=1 rw=rw types=byte */
    uint8_t    _pad_0x1a[0x3];   /* +0x1a pad */
};
```