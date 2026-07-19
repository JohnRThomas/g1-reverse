### cluster param_0128  (param, 3 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: z; 0/3 members are LIBRARY-class)

members (3 shown of 3):
  - cbprintf_package_convert @ 0x4abc0  as param_1  [APPLICATION]
  - z_log_msg_runtime_create @ 0x4d944  as param_3  [APPLICATION]
  - arm_fault_forward_handler @ 0x80780  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0128 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,uint,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```