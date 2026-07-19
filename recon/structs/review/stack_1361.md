## review group stack_1361  (1 cluster(s), kinds=stack)

### proposal for stack_1361
struct_name: lc3_energy_locals | is_library: True | library_name: lc3_energy_compute_locals | is_array: True | confidence: low
purpose: Local array of three accumulator values used by lc3_energy_compute during LC3 spectral energy computation
fields:
  0x0  uint32_t     energy_0  idx4
  0x4  uint32_t     energy_1  idx4
  0x8  uint32_t     energy_2  idx4

<ground-truth bundle for stack_1361>
### cluster stack_1361  (stack, 1 members, 3 fields, size>=0xc)

Stack-frame local local_28 in lc3_energy_compute (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_energy_compute @ 0x68b68  as local_28  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1361 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
