## review group param_0312  (1 cluster(s), kinds=param)

### proposal for param_0312
struct_name: nrfx_uarte_ctx | is_library: True | library_name: nrfx_uarte_t / uarte_nrfx_data_t | is_array: None | confidence: medium
purpose: nrfx UARTE driver instance/config data used by uarte_nrfx_configure and uarte_nrfx_init.
fields:
  0x4  void *       field_0x4  
  0x10  void *       field_0x10  

<ground-truth bundle for param_0312>
### cluster param_0312  (param, 2 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/2 members are LIBRARY-class)

members (2 shown of 2):
  - uarte_nrfx_configure @ 0x62ad8  as param_1  [LIBRARY]
  - uarte_nrfx_init @ 0x62d9c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0312 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    void *     field_0x10;   /* +0x10  sz=4 rw=r types=int,ptr */
};
```
