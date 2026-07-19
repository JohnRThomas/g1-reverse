## review group param_0128  (1 cluster(s), kinds=param)

### proposal for param_0128
struct_name: cbprintf_package_hdr | is_library: True | library_name: Zephyr cbprintf package header (struct cbprintf_package_hdr / z_log_msg internals) | is_array: None | confidence: low
purpose: cbprintf/log message package descriptor shared by cbprintf_package_convert, z_log_msg_runtime_create and (incidentally) arm_fault_forward_handler; three consecutive index-typed words describing a formatted-argument package.
fields:
  0x4  uint32_t     len_or_flags  read-only idx4
  0x8  uint32_t     field_0x8  read-only idx4
  0xc  uint32_t     field_0xc  read-only idx4

<ground-truth bundle for param_0128>
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
