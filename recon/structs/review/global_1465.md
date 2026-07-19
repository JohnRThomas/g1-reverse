## review group global_1465  (1 cluster(s), kinds=global)

### proposal for global_1465
struct_name: trng_source_state | is_library: True | library_name: Nordic CryptoCell TRNG context (CRYS_RND_State_t or similar) | is_array: None | confidence: low
purpose: Internal state object for the CryptoCell/Oberon TRNG accessed by getTrngSource; large opaque region (0x130 bytes) followed by two small status/count words.
fields:
  0x130  uint32_t     field_0x130  read-only, possibly entropy pool counter
  0x138  uint32_t     field_0x138  read-only, possibly state/flags

<ground-truth bundle for global_1465>
### cluster global_1465  (global, 1 members, 2 fields, size>=0x13c)

Global object at fixed address 0x0007a9ac.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - getTrngSource @ 0x7a720  as 0x0007a9ac  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1465 {
    uint8_t    _pad_0x0[0x130];   /* +0x0 pad */
    uint32_t   field_0x130;   /* +0x130  sz=4 rw=r types=int */
    uint8_t    _pad_0x134[0x4];   /* +0x134 pad */
    uint32_t   field_0x138;   /* +0x138  sz=4 rw=r types=int */
};
```
