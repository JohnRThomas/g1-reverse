## review group param_0284  (1 cluster(s), kinds=param)

### proposal for param_0284
struct_name: net_buf_simple | is_library: True | library_name: net_buf_simple | is_array: None | confidence: high
purpose: Zephyr net_buf_simple buffer descriptor manipulated by net_buf_simple_reserve
fields:
  0x4  uint32_t     len  idx4, likely len field
  0x8  uint32_t     size  idx4, likely size field

<ground-truth bundle for param_0284>
### cluster param_0284  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: net_buf; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - net_buf_simple_reserve @ 0x5f4d4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0284 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
