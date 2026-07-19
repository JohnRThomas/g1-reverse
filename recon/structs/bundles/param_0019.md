### cluster param_0019  (param, 2 members, 17 fields, size>=0x6b0)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (2 shown of 2):
  - panel_level_calc_cached @ 0x25ecc  as param_1  [APPLICATION]
  - imu_fusion_thread @ 0xfe88  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0019 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=int */
    uint8_t    _pad_0x10[0xc];   /* +0x10 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=int */
    uint8_t    _pad_0x20[0x20];   /* +0x20 pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=idx4 */
    uint32_t   field_0x44;   /* +0x44  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x48[0x8];   /* +0x48 pad */
    uint32_t   field_0x50;   /* +0x50  sz=4 rw=r types=idx4 */
    uint32_t   field_0x54;   /* +0x54  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x58[0x28];   /* +0x58 pad */
    uint32_t   field_0x80;   /* +0x80  sz=4 rw=r types=int */
    uint32_t   field_0x84;   /* +0x84  sz=4 rw=r types=int */
    uint32_t   field_0x88;   /* +0x88  sz=4 rw=r types=int */
    uint8_t    _pad_0x8c[0xec];   /* +0x8c pad */
    uint16_t   field_0x178;   /* +0x178  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x17a[0x1e];   /* +0x17a pad */
    uint32_t   field_0x198;   /* +0x198  sz=4 rw=w types=int */
    uint32_t   field_0x19c;   /* +0x19c  sz=4 rw=w types=int */
    uint32_t   field_0x1a0;   /* +0x1a0  sz=4 rw=w types=int */
    uint8_t    _pad_0x1a4[0x264];   /* +0x1a4 pad */
    uint32_t   field_0x408;   /* +0x408  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x40c[0xc];   /* +0x40c pad */
    uint32_t   field_0x418;   /* +0x418  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x41c[0x290];   /* +0x41c pad */
    uint32_t   field_0x6ac;   /* +0x6ac  sz=4 rw=r types=idx4 */
};
```