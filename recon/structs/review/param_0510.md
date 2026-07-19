## review group param_0510  (1 cluster(s), kinds=param)

### proposal for param_0510
struct_name: cbprintf_cpy_ctx | is_library: True | library_name: Zephyr cbprintf internal (cbprintf_cpy helper) | is_array: None | confidence: low
purpose: Zephyr cbprintf internal copy-descriptor context used by z_cbprintf_cpy: destination pointer/length pair.
fields:
  0x4  uint32_t     dst_or_len_a  
  0x8  uint32_t     dst_or_len_b  

<ground-truth bundle for param_0510>
### cluster param_0510  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: z; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - z_cbprintf_cpy @ 0x7ee48  as param_3  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0510 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
