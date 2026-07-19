## review group param_0342  (1 cluster(s), kinds=param)

### proposal for param_0342
struct_name: nrfx_spim_ctx | is_library: True | library_name: nrfx_spim_t | is_array: None | confidence: medium
purpose: nrfx SPIM peripheral instance/config used by nrfx_spim_configure and nrfx_spim_init.
fields:
  0x1  uint8_t      field_0x1  
  0x4  uint8_t      field_0x4  

<ground-truth bundle for param_0342>
### cluster param_0342  (param, 2 members, 2 fields, size>=0x5)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - nrfx_spim_configure @ 0x66ec0  as param_1  [APPLICATION]
  - nrfx_spim_init @ 0x671d8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0342 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=byte */
};
```
