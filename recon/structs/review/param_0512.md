## review group param_0512  (1 cluster(s), kinds=param)

### proposal for param_0512
struct_name: log_output_ctx | is_library: True | library_name: log_output_control_block / log_output | is_array: None | confidence: medium
purpose: Zephyr logging output context flushed by log_output_flush
fields:
  0x0  uint32_t     flags_or_func  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for param_0512>
### cluster param_0512  (param, 1 members, 3 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: log; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - log_output_flush @ 0x7eece  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0512 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
