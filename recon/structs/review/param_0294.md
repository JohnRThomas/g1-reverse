## review group param_0294  (1 cluster(s), kinds=param)

### proposal for param_0294
struct_name: pdm_clock_config | is_library: False | library_name:  | is_array: False | confidence: low
purpose: PDM clock/init configuration consumed by pdm_configure_clock_and_init.
fields:
  0x4  void *       clock_handler  
  0x10  int32_t      clock_freq_or_mode  

<ground-truth bundle for param_0294>
### cluster param_0294  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - pdm_configure_clock_and_init @ 0x5fc7c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0294 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
