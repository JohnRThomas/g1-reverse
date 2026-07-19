## review group param_0411  (1 cluster(s), kinds=param)

### proposal for param_0411
struct_name: sched_thread_ctx | is_library: True | library_name: struct k_thread (Zephyr, partial) | is_array: None | confidence: low
purpose: Thread control object inspected by sched_thread_should_preempt to read a priority byte and a state/flags short.
fields:
  0xd  uint8_t      priority  
  0xe  uint16_t     thread_state  

<ground-truth bundle for param_0411>
### cluster param_0411  (param, 1 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - sched_thread_should_preempt @ 0x736ec  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0411 {
    uint8_t    _pad_0x0[0xd];   /* +0x0 pad */
    uint8_t    field_0xd;   /* +0xd  sz=1 rw=r types=byte */
    uint16_t   field_0xe;   /* +0xe  sz=1,2 rw=r types=char,ushort */
};
```
