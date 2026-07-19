## review group param_0645  (1 cluster(s), kinds=param)

### proposal for param_0645
struct_name: net_buf_simple | is_library: True | library_name: net_buf_simple | is_array: None | confidence: medium
purpose: Zephyr net_buf_simple buffer descriptor initialized by net_buf_simple_init_with_data (len/size fields plus backing data pointer).
fields:
  0x1  uint16_t     len  write-only
  0x6  uint16_t     size  write-only
  0x8  uint32_t     buf_ptr  read as idx4, backing __buf pointer

<ground-truth bundle for param_0645>
### cluster param_0645  (param, 1 members, 3 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: net_buf; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - net_buf_simple_init_with_data @ 0x836ec  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0645 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint16_t   field_0x1;   /* +0x1  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x3[0x3];   /* +0x3 pad */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=w types=undefined2 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
