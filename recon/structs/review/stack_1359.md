## review group stack_1359  (1 cluster(s), kinds=stack)

### proposal for stack_1359
struct_name: lc3_bwdet_energy_array | is_library: True | library_name: lc3 (Bluetooth LE Audio codec) | is_array: True | confidence: medium
purpose: Stack-local array of subband energy accumulators inside the LC3 bandwidth-detector routine lc3_bwdet_run (Ghidra af-prefix naming indicates an array-of-float local)
fields:
  0x0  float        energy_0  
  0x4  float        energy_1  
  0x8  float        energy_2  
  0xc  float        energy_3  
  0x14  float        energy_4  gap at 0x10 suggests non-uniform stride/padding

<ground-truth bundle for stack_1359>
### cluster stack_1359  (stack, 1 members, 5 fields, size>=0x18)

Stack-frame local afStack_30 in lc3_bwdet_run (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_bwdet_run @ 0x68a10  as afStack_30  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1359 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x10[0x4];   /* +0x10 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```
