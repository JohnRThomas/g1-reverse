## review group param_0340  (1 cluster(s), kinds=param)

### proposal for param_0340
struct_name: nrfx_pin_freq_cfg | is_library: True | library_name: nrfx (QSPI pin config, application-side struct) | is_array: None | confidence: low
purpose: Pin/frequency validation configuration passed to nrfx_pin_freq_config_validate
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x14  uint32_t     field_0x14  
  0x1c  uint32_t     field_0x1c  
  0x21  uint8_t      field_0x21  
  0x23  uint8_t      field_0x23  
  0x24  uint32_t     field_0x24  

<ground-truth bundle for param_0340>
### cluster param_0340  (param, 1 members, 8 fields, size>=0x28)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_pin_freq_config_validate @ 0x66d78  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0340 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x4];   /* +0x10 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x4];   /* +0x18 pad */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x20[0x1];   /* +0x20 pad */
    uint8_t    field_0x21;   /* +0x21  sz=1 rw=r types=char */
    uint8_t    _pad_0x22[0x1];   /* +0x22 pad */
    uint8_t    field_0x23;   /* +0x23  sz=1 rw=r types=char */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
};
```
