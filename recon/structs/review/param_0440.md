## review group param_0440  (1 cluster(s), kinds=param)

### proposal for param_0440
struct_name: mbedtls_entropy_context | is_library: True | library_name: mbedtls_entropy_context | is_array: None | confidence: medium
purpose: mbed TLS entropy context used by entropy_gather_internal_part_0 and cc_mbedtls_entropy_func to accumulate entropy from sources.
fields:
  0xf8  uint32_t     source_count  number of registered entropy sources
  0xfc  void*        mutex_or_ctx  pointer, e.g. threading mutex
  0x100  uint32_t     field_0x100  accumulator/state word
  0x104  uint32_t     field_0x104  accumulator/state word, read-write
  0x108  uint32_t     field_0x108  accumulator/state word
  0x10c  uint32_t     field_0x10c  accumulator/state word

<ground-truth bundle for param_0440>
### cluster param_0440  (param, 2 members, 6 fields, size>=0x110)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 2/2 members are LIBRARY-class)

members (2 shown of 2):
  - entropy_gather_internal_part_0 @ 0x79f50  as param_1  [LIBRARY]
  - cc_mbedtls_entropy_func @ 0x7a05c  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0440 {
    uint8_t    _pad_0x0[0xf8];   /* +0x0 pad */
    uint32_t   field_0xf8;   /* +0xf8  sz=4 rw=r types=int */
    void *     field_0xfc;   /* +0xfc  sz=4 rw=r types=ptr */
    uint32_t   field_0x100;   /* +0x100  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x104;   /* +0x104  sz=4 rw=rw types=int,uint */
    uint32_t   field_0x108;   /* +0x108  sz=4 rw=r types=uint */
    uint32_t   field_0x10c;   /* +0x10c  sz=4 rw=r types=int */
};
```
