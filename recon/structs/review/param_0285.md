## review group param_0285  (1 cluster(s), kinds=param)

### proposal for param_0285
struct_name: net_buf_simple | is_library: True | library_name: net_buf_simple | is_array: False | confidence: high
purpose: Zephyr net_buf_simple structure passed to net_buf_simple_push (data pointer + len fields).
fields:
  0x1  uint16_t     len  buffer length
  0x4  void *       data  data pointer
  0x8  uint32_t     size  buffer size

<ground-truth bundle for param_0285>
### cluster param_0285  (param, 1 members, 3 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: net_buf; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - net_buf_simple_push @ 0x5f518  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0285 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint16_t   field_0x1;   /* +0x1  sz=2 rw=w types=short */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
