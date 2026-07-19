## review group param_0388  (1 cluster(s), kinds=param)

### proposal for param_0388
struct_name: lc3_side_info | is_library: True | library_name: lc3_side_data | is_array: None | confidence: low
purpose: LC3 codec spectral 'side' encoding data structure used by lc3_spec_put_side
fields:
  0x2  uint8_t      field_0x2  byte
  0x4  uint32_t     field_0x4  idx4

<ground-truth bundle for param_0388>
### cluster param_0388  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_spec_put_side @ 0x6f91c  as param_4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0388 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=byte */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
