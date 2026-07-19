### cluster param_0673  (param, 2 members, 7 fields, size>=0x1a)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - flash_page_index_lookup @ 0x84602  as param_1  [APPLICATION]
  - layout_select_region @ 0x84774  as param_1  [APPLICATION]

layout notes: overlap at 0x5 (prev field ends 0x8)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0673 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=ushort */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x2];   /* +0x8 pad */
    uint16_t   field_0xa;   /* +0xa  sz=2 rw=r types=ushort */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x14[0x2];   /* +0x14 pad */
    uint16_t   field_0x16;   /* +0x16  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x18[0x2];   /* +0x18 pad */
};
```