## review group param_0410  (1 cluster(s), kinds=param)

### proposal for param_0410
struct_name: k_work_q | is_library: True | library_name: k_work_q | is_array: None | confidence: medium
purpose: Zephyr k_work_q work-queue struct accessed by k_work_queue_drain (queue list/thread offset region and a flags word)
fields:
  0xd8  uint32_t     flags  
  0xf0  uint32_t     drain_sem_or_count  

<ground-truth bundle for param_0410>
### cluster param_0410  (param, 1 members, 2 fields, size>=0xf4)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: k; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - k_work_queue_drain @ 0x731b8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0410 {
    uint8_t    _pad_0x0[0xd8];   /* +0x0 pad */
    uint32_t   field_0xd8;   /* +0xd8  sz=4 rw=r types=int */
    uint8_t    _pad_0xdc[0x14];   /* +0xdc pad */
    uint32_t   field_0xf0;   /* +0xf0  sz=4 rw=rw types=uint */
};
```
