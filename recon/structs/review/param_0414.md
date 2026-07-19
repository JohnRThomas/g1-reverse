## review group param_0414  (1 cluster(s), kinds=param)

### proposal for param_0414
struct_name: k_timer | is_library: True | library_name: k_timer | is_array: False | confidence: medium
purpose: Zephyr kernel timer object (embeds a struct _timeout) manipulated by remove_timeout/z_add_timeout/z_impl_k_timer_start
fields:
  0x4  void *       timeout_node_next  sys_dnode next
  0x8  void *       timeout_node_prev  sys_dnode prev
  0x10  void *       timeout_fn  _timeout.fn callback
  0x14  int32_t      timeout_dticks  
  0x28  void *       expiry_fn  k_timer expiry_fn, written on start
  0x2c  void *       stop_fn  written on start
  0x30  void *       user_data  written on start

<ground-truth bundle for param_0414>
### cluster param_0414  (param, 3 members, 7 fields, size>=0x34)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: z; 1/3 members are LIBRARY-class)

members (3 shown of 3):
  - remove_timeout @ 0x74bbc  as param_1  [LIBRARY]
  - z_add_timeout @ 0x74bf4  as param_1  [APPLICATION]
  - z_impl_k_timer_start @ 0x75174  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0414 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x18[0x10];   /* +0x18 pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x2c;   /* +0x2c  sz=4 rw=w types=undefined4 */
    uint32_t   field_0x30;   /* +0x30  sz=4 rw=w types=undefined4 */
};
```
