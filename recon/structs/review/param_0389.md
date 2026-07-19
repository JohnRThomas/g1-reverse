## review group param_0389  (1 cluster(s), kinds=param)

### proposal for param_0389
struct_name: lc3_spec_encode_ctx | is_library: True | library_name: lc3 codec internal (LC3plus/liblc3) | is_array: False | confidence: low
purpose: Parameter passed to lc3_spec_encode (LC3 audio codec spectral encoding); small scalar/flag structure.
fields:
  0x4  int32_t      field_0x4  
  0x8  uint8_t      field_0x8  byte flag

<ground-truth bundle for param_0389>
### cluster param_0389  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_spec_encode @ 0x6f9c0  as param_7  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0389 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint8_t    field_0x8;   /* +0x8  sz=1 rw=r types=byte */
    uint8_t    _pad_0x9[0x3];   /* +0x9 pad */
};
```
