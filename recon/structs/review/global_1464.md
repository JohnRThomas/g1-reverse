## review group global_1464  (1 cluster(s), kinds=global)

### proposal for global_1464
struct_name: trng_hw_context | is_library: True | library_name: CryptoCell TRNG driver context (CC3xx/nrf_cc3xx-style, exact header unverified) | is_array: False | confidence: low
purpose: Hardware TRNG (true random number generator) driver context initialized/started by startTrngHW; large buffer with two trailing status/count words.
fields:
  0x1c4  uint32_t     trng_status  write-only word after large opaque buffer
  0x1d8  uint32_t     trng_byte_count  write-only uint, likely bytes-generated counter

<ground-truth bundle for global_1464>
### cluster global_1464  (global, 1 members, 2 fields, size>=0x1dc)

Global object at fixed address 0x0007a62c.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - startTrngHW @ 0x7a50c  as 0x0007a62c  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1464 {
    uint8_t    _pad_0x0[0x1c4];   /* +0x0 pad */
    uint32_t   field_0x1c4;   /* +0x1c4  sz=4 rw=w types=undefined4 */
    uint8_t    _pad_0x1c8[0x10];   /* +0x1c8 pad */
    uint32_t   field_0x1d8;   /* +0x1d8  sz=4 rw=w types=uint */
};
```
