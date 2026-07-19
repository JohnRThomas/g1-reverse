## review group param_0486  (1 cluster(s), kinds=param)

### proposal for param_0486
struct_name: u32le_array | is_library: False | library_name:  | is_array: True | confidence: medium
purpose: Little-endian uint32 array target buffer written/read by bytes_to_u32le_array.
fields:
  0x4  uint32_t     words[0]  array element, uniform stride 4
  0x8  uint32_t     words[1]  array element
  0xc  uint32_t     words[2]  array element

<ground-truth bundle for param_0486>
### cluster param_0486  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - bytes_to_u32le_array @ 0x7d8c4  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0486 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
