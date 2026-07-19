## review group stack_1423  (1 cluster(s), kinds=stack)

### proposal for stack_1423
struct_name: snprintf_locals | is_library: True | library_name: newlib/picolibc snprintf internal | is_array: None | confidence: low
purpose: Local scratch struct inside the C library snprintf implementation (format-state words)
fields:
  0x0  uint32_t     field_0x0  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for stack_1423>
### cluster stack_1423  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_80 in snprintf (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - snprintf @ 0x77914  as local_80  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1423 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
