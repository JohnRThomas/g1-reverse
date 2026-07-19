## review group param_0334  (1 cluster(s), kinds=param)

### proposal for param_0334
struct_name: nrfx_pdm_config_small | is_library: True | library_name: nrfx_pdm_config_t (Nordic nrfx PDM driver, tail fields) | is_array: None | confidence: low
purpose: Small PDM configuration record read by nrfx_pdm_init: two pin/mode bytes followed by a further mode byte.
fields:
  0x10  uint8_t      mode  byte
  0x11  uint8_t      edge  byte
  0x15  uint8_t      gain_or_flag  undefined1 byte

<ground-truth bundle for param_0334>
### cluster param_0334  (param, 1 members, 3 fields, size>=0x16)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_pdm_init @ 0x6615c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0334 {
    uint8_t    _pad_0x0[0x10];   /* +0x0 pad */
    uint8_t    field_0x10;   /* +0x10  sz=1 rw=r types=byte */
    uint8_t    field_0x11;   /* +0x11  sz=1 rw=r types=byte */
    uint8_t    _pad_0x12[0x3];   /* +0x12 pad */
    uint8_t    field_0x15;   /* +0x15  sz=1 rw=r types=undefined1 */
};
```
