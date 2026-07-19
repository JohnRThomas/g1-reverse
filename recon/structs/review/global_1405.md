## review group global_1405  (1 cluster(s), kinds=global)

### proposal for global_1405
struct_name: z_kernel_sched_state | is_library: True | library_name: _kernel / _ready_q | is_array: None | confidence: low
purpose: Zephyr kernel scheduler global state touched by z_reschedule (ready-queue / cpu bitmask style fields)
fields:
  0x8  int          field_0x8  possibly ready_q cache or cpu idle flag
  0x18  int          field_0x18  possibly dlist head/tail pointer

<ground-truth bundle for global_1405>
### cluster global_1405  (global, 1 members, 2 fields, size>=0x1c)

Global object at fixed address 0x00073a64.

library hint: LIKELY LIBRARY (prefixes: z; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - z_reschedule @ 0x739f0  as 0x00073a64  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1405 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    uint8_t    _pad_0xc[0xc];   /* +0xc pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=int */
};
```
