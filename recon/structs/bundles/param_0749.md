### cluster param_0749  (param, 1 members, 6 fields, size>=0x44)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - stdio_reset_ungetc_buffer @ 0x87862  as param_2  [APPLICATION]

layout notes: overlap at 0x4 (prev field ends 0x5)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0749 {
    uint8_t    _pad_0x0[0x3];   /* +0x0 pad */
    uint16_t   field_0x3;   /* +0x3  sz=2 rw=rw types=ushort */
    uint8_t    _pad_0x5[0xb];   /* +0x5 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14[0x20];   /* +0x14 pad */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x38[0x4];   /* +0x38 pad */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
};
```