## review group param_0403  (1 cluster(s), kinds=param)

### proposal for param_0403
struct_name: k_mem_slab | is_library: True | library_name: struct k_mem_slab | is_array: None | confidence: high
purpose: Zephyr kernel memory slab allocator object used by k_mem_slab_free.
fields:
  0xc  uint32_t     num_blocks  
  0x10  uint32_t     block_size  
  0x14  void *       buffer  
  0x18  void *       free_list  
  0x1c  uint32_t     num_used  

<ground-truth bundle for param_0403>
### cluster param_0403  (param, 1 members, 5 fields, size>=0x20)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: k; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - k_mem_slab_free @ 0x71cf4  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0403 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=uint */
    void *     field_0x14;   /* +0x14  sz=4 rw=r types=ptr */
    void *     field_0x18;   /* +0x18  sz=4 rw=rw types=int,ptr,undefined4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=rw types=int */
};
```
