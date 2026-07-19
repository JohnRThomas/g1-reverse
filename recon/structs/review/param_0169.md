## review group param_0169  (1 cluster(s), kinds=param)

### proposal for param_0169
struct_name: mem_region | is_library: True | library_name: struct sys_mem_blocks / region descriptor (generic base+size) | is_array: None | confidence: low
purpose: Memory region descriptor (base/size) passed to library region_init
fields:
  0x8  uint32_t     base  
  0xc  uint32_t     size  

<ground-truth bundle for param_0169>
### cluster param_0169  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - region_init @ 0x50bf0  as param_2  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0169 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
