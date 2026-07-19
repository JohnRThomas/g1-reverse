## review group param_0740  (1 cluster(s), kinds=param)

### proposal for param_0740
struct_name: k_poll_signal | is_library: True | library_name: k_poll_signal | is_array: None | confidence: high
purpose: Zephyr kernel poll signal object initialized by z_impl_k_poll_signal_init
fields:
  0x0  uint32_t     type_or_flags  
  0x4  int          signaled  
  0x8  int          result  

<ground-truth bundle for param_0740>
### cluster param_0740  (param, 1 members, 3 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: z; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - z_impl_k_poll_signal_init @ 0x868aa  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0740 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=w types=int */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=w types=undefined4 */
};
```
