### cluster param_0058  (param, 1 members, 8 fields, size>=0xd4)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - process_box_event @ 0x254d8  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0058 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x4];   /* +0x10 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x18];   /* +0x18 pad */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x34[0x18];   /* +0x34 pad */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x50[0x4];   /* +0x50 pad */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x58[0x78];   /* +0x58 pad */
    uint32_t   field_0xd0;   /* +0xd0  sz=4 rw=r types=idx4 */
};
```