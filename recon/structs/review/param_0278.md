## review group param_0278  (1 cluster(s), kinds=param)

### proposal for param_0278
struct_name: net_buf_slist_node | is_library: True | library_name: sys_snode_t | is_array: False | confidence: medium
purpose: Zephyr net_buf singly-linked-list node/head passed to net_buf_slist_put
fields:
  0x0  uint32_t     next_or_head  
  0x4  uint32_t     tail_or_count  

<ground-truth bundle for param_0278>
### cluster param_0278  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: net_buf; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - net_buf_slist_put @ 0x5f074  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0278 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
