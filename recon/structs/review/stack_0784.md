## review group stack_0784  (1 cluster(s), kinds=stack)

### proposal for stack_0784
struct_name: cbvprintf_state | is_library: True | library_name: z_cbvprintf_impl local state (Zephyr sys/cbprintf) | is_array: None | confidence: low
purpose: Compiler-generated local scratch pair (pointer + counter) inside Zephyr's z_cbvprintf_impl formatting loop.
fields:
  0x0  void *       field_0x0  
  0x4  uint32_t     field_0x4  

<ground-truth bundle for stack_0784>
### cluster stack_0784  (stack, 1 members, 2 fields, size>=0x8)

Stack-frame local local_60 in z_cbvprintf_impl (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: z; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - z_cbvprintf_impl @ 0x113a8  as local_60  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0784 {
    void *     field_0x0;   /* +0x0  sz=2,4 rw=w types=ptr,short */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=w types=int */
};
```
