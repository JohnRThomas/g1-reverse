### cluster param_0148  (param, 1 members, 3 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: log; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - log_output_msg_process @ 0x4ddf8  as param_2  [LIBRARY]

layout notes: overlap at 0x2 (prev field ends 0x4)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0148 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=int */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,undefined4 */
};
```