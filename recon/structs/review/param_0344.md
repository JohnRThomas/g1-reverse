## review group param_0344  (1 cluster(s), kinds=param)

### proposal for param_0344
struct_name: nrfx_spim_ctx | is_library: True | library_name: nrfx_spim_t | is_array: None | confidence: low
purpose: nrfx SPIM peripheral instance control block accessed on uninit
fields:
  0x1  uint8_t      drv_inst_idx  
  0x4  uint32_t     p_reg_or_flags  

<ground-truth bundle for param_0344>
### cluster param_0344  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_spim_uninit @ 0x67248  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0344 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
