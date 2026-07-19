### cluster param_0447  (param, 3 members, 10 fields, size>=0x60)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: mbedtls; 3/3 members are LIBRARY-class)

members (3 shown of 3):
  - mbedtls_sha_starts_internal @ 0x7acb8  as param_1  [LIBRARY]
  - RNG_PLAT_SetUserRngParameters @ 0x7af78  as param_1  [LIBRARY]
  - CC_PalTrngParamGet @ 0x7afec  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0447 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x28[0x34];   /* +0x28 pad */
    uint32_t   field_0x5c;   /* +0x5c  sz=4 rw=r types=idx4 */
};
```