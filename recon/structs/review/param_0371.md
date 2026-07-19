## review group param_0371  (1 cluster(s), kinds=param)

### proposal for param_0371
struct_name: lc3_bitstream | is_library: True | library_name: lc3_bits | is_array: None | confidence: medium
purpose: LC3 audio codec bitstream reader state used by lc3_load_s24: bit position/count and trailing size + data pointer
fields:
  0x8  uint32_t     bit_pos  read-only idx4
  0x4a0  uint32_t     nbytes  read-only int
  0x4a4  void *       data  read-only pointer to sample buffer

<ground-truth bundle for param_0371>
### cluster param_0371  (param, 1 members, 3 fields, size>=0x4a8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_load_s24 @ 0x68d90  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0371 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x494];   /* +0xc pad */
    uint32_t   field_0x4a0;   /* +0x4a0  sz=4 rw=r types=int */
    void *     field_0x4a4;   /* +0x4a4  sz=4 rw=r types=ptr */
};
```
