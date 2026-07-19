### cluster param_0419  (param, 1 members, 13 fields, size>=0x68)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - newlib_stdio_init_stream @ 0x76b48  as param_1  [APPLICATION]

layout notes: overlap at 0x4 (prev field ends 0x5)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0419 {
    uint8_t    _pad_0x0[0x3];   /* +0x0 pad */
    uint16_t   field_0x3;   /* +0x3  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x5[0x3];   /* +0x5 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x2];   /* +0xc pad */
    uint16_t   field_0xe;   /* +0xe  sz=2 rw=w types=undefined2 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1c[0x4];   /* +0x1c pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x34[0x30];   /* +0x34 pad */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=r types=idx4 */
};
```