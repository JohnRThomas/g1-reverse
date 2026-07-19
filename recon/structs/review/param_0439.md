## review group param_0439  (1 cluster(s), kinds=param)

### proposal for param_0439
struct_name: ctr_drbg_seed_material | is_library: True | library_name: mbedtls_ctr_drbg_context (internal seed buffer) | is_array: True | confidence: medium
purpose: CTR_DRBG internal working buffer (seed/tmp block) accessed uniformly by ctr_drbg_update_internal.
fields:
  0x4  uint32_t     word_0  
  0x8  uint32_t     word_1  
  0xc  uint32_t     word_2  
  0x10  uint32_t     word_3  
  0x14  uint32_t     word_4  
  0x18  uint32_t     word_5  
  0x1c  uint32_t     word_6  
  0x20  uint32_t     word_7  
  0x24  uint32_t     word_8  
  0x28  uint32_t     word_9  
  0x2c  uint32_t     word_10  

<ground-truth bundle for param_0439>
### cluster param_0439  (param, 1 members, 11 fields, size>=0x30)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - ctr_drbg_update_internal @ 0x799ec  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0439 {
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
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=r types=idx4 */
};
```
