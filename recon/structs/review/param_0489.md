## review group param_0489  (1 cluster(s), kinds=param)

### proposal for param_0489
struct_name: cbprintf_out_ctx | is_library: True | library_name: cbprintf internal context | is_array: False | confidence: low
purpose: Zephyr cbprintf external formatting output context (buffer pointer/size/index) used by cbpprintf_external
fields:
  0x4  char *       out_buf  
  0x8  uint32_t     out_size  
  0xc  uint32_t     out_idx  

<ground-truth bundle for param_0489>
### cluster param_0489  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: -; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - cbpprintf_external @ 0x7db9e  as param_4  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0489 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
