## review group stack_1373  (1 cluster(s), kinds=stack)

### proposal for stack_1373
struct_name: lc3_ltpf_locals | is_library: True | library_name: lc3 internal LTPF calc (local) | is_array: None | confidence: low
purpose: Local scratch in lc3_ltpf_analyse (LC3 codec Long-Term Postfilter analysis) holding pitch-lag/gain style intermediate values.
fields:
  0x0  uint32_t     pitch_lag  read as idx4
  0x4  uint32_t     gain  read as idx4
  0xc  uint32_t     correlation  read as idx4

<ground-truth bundle for stack_1373>
### cluster stack_1373  (stack, 1 members, 3 fields, size>=0x10)

Stack-frame local local_7c in lc3_ltpf_analyse (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_ltpf_analyse @ 0x6ab80  as local_7c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1373 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x4];   /* +0x8 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
