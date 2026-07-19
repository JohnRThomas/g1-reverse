## review group param_0498  (1 cluster(s), kinds=param)

### proposal for param_0498
struct_name: sys_notify | is_library: True | library_name: sys_notify | is_array: None | confidence: high
purpose: Zephyr sys_notify async-operation notification structure validated by sys_notify_validate
fields:
  0x4  uint32_t     flags  idx4
  0x8  uint32_t     callback_or_sem  idx4, union of callback ptr / k_sem ptr

<ground-truth bundle for param_0498>
### cluster param_0498  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: sys; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - sys_notify_validate @ 0x7e238  as param_1  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0498 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
