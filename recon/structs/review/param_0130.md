## review group param_0130  (1 cluster(s), kinds=param)

### proposal for param_0130
struct_name: sys_notify | is_library: True | library_name: sys_notify | is_array: None | confidence: medium
purpose: Zephyr async-notify completion object finalized by sys_notify_finalize
fields:
  0x4  uint32_t     method  r, likely union pointer (signal/callback)
  0x8  uint32_t     userdata_or_extra  r

<ground-truth bundle for param_0130>
### cluster param_0130  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: sys; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - sys_notify_finalize @ 0x4bb0c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0130 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
