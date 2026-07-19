### cluster param_0438  (param, 4 members, 17 fields, size>=0x9c)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: mbedtls; 4/4 members are LIBRARY-class)

members (4 shown of 4):
  - ctr_drbg_update_internal @ 0x799ec  as param_1  [LIBRARY]
  - mbedtls_ctr_drbg_reseed_internal @ 0x79b60  as param_1  [LIBRARY]
  - cc_mbedtls_ctr_drbg_seed @ 0x79c50  as param_1  [LIBRARY]
  - cc_mbedtls_ctr_drbg_random_with_add @ 0x79cf0  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0438 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=rw types=idx4,int,uint,undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4,int */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=rw types=idx4,int,uint,undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4,int */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x34;   /* +0x34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x38;   /* +0x38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x40[0x54];   /* +0x40 pad */
    void *     field_0x94;   /* +0x94  sz=4 rw=rw types=ptr,undefined4 */
    uint32_t   field_0x98;   /* +0x98  sz=4 rw=rw types=undefined4 */
};
```