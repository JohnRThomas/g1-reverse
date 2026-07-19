## review group param_0685  (1 cluster(s), kinds=param)

### proposal for param_0685
struct_name: wdt_nrf_config | is_library: True | library_name: wdt_nrf_data | is_array: None | confidence: medium
purpose: nRF watchdog driver setup config used by wdt_nrf_setup
fields:
  0x4  void *       reg_base_or_cfg_ptr  
  0x10  uint32_t     timeout_or_flags  

<ground-truth bundle for param_0685>
### cluster param_0685  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - wdt_nrf_setup @ 0x84cfa  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0685 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
