## review group param_0090  (1 cluster(s), kinds=param)

### proposal for param_0090
struct_name: brightness_lum_state | is_library: False | library_name:  | is_array: False | confidence: low
purpose: State struct for set_brightness_lum_base holding a brightness level and a raw luminance value.
fields:
  0x4  uint8_t      lum_level  brightness level byte
  0x5  uint16_t     lum_raw  raw luminance/base value

<ground-truth bundle for param_0090>
### cluster param_0090  (param, 1 members, 2 fields, size>=0x7)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - set_brightness_lum_base @ 0x31cbc  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0090 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=char */
    uint16_t   field_0x5;   /* +0x5  sz=2 rw=r types=ushort */
};
```
