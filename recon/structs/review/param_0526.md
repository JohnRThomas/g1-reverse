## review group param_0526  (1 cluster(s), kinds=param)

### proposal for param_0526
struct_name: settings_nvs_backend_cfg | is_library: True | library_name: settings_nvs | is_array: None | confidence: low
purpose: Zephyr settings NVS backend init configuration (fs handle, sector info, callback)
fields:
  0x30  int          nvs_init_result  
  0x38  uint16_t     sector_size_or_cnt  
  0x3c  uint32_t     backend_flags  

<ground-truth bundle for param_0526>
### cluster param_0526  (param, 1 members, 3 fields, size>=0x40)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: settings; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - settings_nvs_backend_init @ 0x7f344  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0526 {
    uint8_t    _pad_0x0[0x30];   /* +0x0 pad */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=w types=int */
    uint8_t    _pad_0x34[0x4];   /* +0x34 pad */
    uint16_t   field_0x38;   /* +0x38  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x3a[0x2];   /* +0x3a pad */
    uint32_t   field_0x3c;   /* +0x3c  sz=4 rw=r types=int */
};
```
