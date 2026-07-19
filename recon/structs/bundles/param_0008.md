### cluster param_0008  (param, 1 members, 27 fields, size>=0x1778)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - battery_soc_curve_model_init @ 0xe53c  as param_8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0008 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x40];   /* +0x8 pad */
    uint32_t   field_0x48;   /* +0x48  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4c;   /* +0x4c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=r types=idx4 */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=idx4 */
    uint32_t   field_0x5c;   /* +0x5c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x60[0xc8];   /* +0x60 pad */
    uint32_t   field_0x128;   /* +0x128  sz=4 rw=r types=idx4 */
    uint32_t   field_0x12c;   /* +0x12c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x130;   /* +0x130  sz=4 rw=r types=idx4 */
    uint32_t   field_0x134;   /* +0x134  sz=4 rw=r types=idx4 */
    uint32_t   field_0x138;   /* +0x138  sz=4 rw=r types=idx4 */
    uint32_t   field_0x13c;   /* +0x13c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x140;   /* +0x140  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x144[0x48f];   /* +0x144 pad */
    uint8_t    field_0x5d3;   /* +0x5d3  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x5d4[0x1170];   /* +0x5d4 pad */
    uint32_t   field_0x1744;   /* +0x1744  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1748;   /* +0x1748  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x174c[0x4];   /* +0x174c pad */
    uint32_t   field_0x1750;   /* +0x1750  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1754;   /* +0x1754  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1758;   /* +0x1758  sz=4 rw=r types=idx4 */
    uint32_t   field_0x175c;   /* +0x175c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1760;   /* +0x1760  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1764;   /* +0x1764  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1768;   /* +0x1768  sz=4 rw=r types=idx4 */
    uint32_t   field_0x176c;   /* +0x176c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1770;   /* +0x1770  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1774;   /* +0x1774  sz=4 rw=r types=idx4 */
};
```