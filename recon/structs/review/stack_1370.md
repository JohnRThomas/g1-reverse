## review group stack_1370  (1 cluster(s), kinds=stack)

### proposal for stack_1370
struct_name: lc3_ltpf_pitch_locals | is_library: True | library_name: liblc3 ltpf pitch detection working buffer | is_array: True | confidence: low
purpose: Local working buffer in library function lc3_ltpf_detect_pitch (LC3 codec long-term pitch prediction) holding a correlation/energy array.
fields:
  0x0  uint32_t     field_0x0  
  0x18c  uint32_t     field_0x18c  

<ground-truth bundle for stack_1370>
### cluster stack_1370  (stack, 1 members, 2 fields, size>=0x190)

Stack-frame local local_1b0 in lc3_ltpf_detect_pitch (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_ltpf_detect_pitch @ 0x698d0  as local_1b0  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1370 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x188];   /* +0x4 pad */
    uint32_t   field_0x18c;   /* +0x18c  sz=4 rw=r types=idx4 */
};
```
