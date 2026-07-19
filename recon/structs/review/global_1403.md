## review group global_1403  (1 cluster(s), kinds=global)

### proposal for global_1403
struct_name: sched_update_cache | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Global scheduler cache holding a count and two pointers, used by sched_update_cache
fields:
  0x8  uint32_t     count  
  0xc  void *       list_head  
  0x1c  void *       aux_ptr  

<ground-truth bundle for global_1403>
### cluster global_1403  (global, 1 members, 3 fields, size>=0x20)

Global object at fixed address 0x0007382c.

library hint: likely G1-original

members (1 shown of 1):
  - sched_update_cache @ 0x737d8  as 0x0007382c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1403 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    void *     field_0xc;   /* +0xc  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x10[0xc];   /* +0x10 pad */
    void *     field_0x1c;   /* +0x1c  sz=4 rw=r types=ptr */
};
```
