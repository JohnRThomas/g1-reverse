## review group param_0442  (1 cluster(s), kinds=param)

### proposal for param_0442
struct_name: cc_trng_ctx | is_library: True | library_name: CryptoCell LLF_RND (proprietary) | is_array: False | confidence: low
purpose: Arm CryptoCell TRNG (true random number generator) hardware context used by startTrngHW/getTrngSource/LLF_RND_GetFastestRosc
fields:
  0x10  uint32_t     rosc_freq_or_source  
  0x14  uint32_t     trng_flags0  
  0x18  uint32_t     trng_flags1  
  0x20  uint32_t     sample_count  
  0x24  int32_t      result_code  

<ground-truth bundle for param_0442>
### cluster param_0442  (param, 3 members, 5 fields, size>=0x28)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 3/3 members are LIBRARY-class)

members (3 shown of 3):
  - startTrngHW @ 0x7a50c  as param_2  [LIBRARY]
  - getTrngSource @ 0x7a720  as param_2  [LIBRARY]
  - LLF_RND_GetFastestRosc @ 0x7b0ec  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0442 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=uint */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0x1c[0x4];   /* +0x1c pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=int,uint */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=int */
};
```
