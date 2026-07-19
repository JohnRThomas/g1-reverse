## review group stack_1387  (1 cluster(s), kinds=stack)

### proposal for stack_1387
struct_name: lc3_tns_analyze_local | is_library: True | library_name: lc3 (liblc3 tns analysis local buffer) | is_array: True | confidence: low
purpose: Local scratch buffer of five words used in lc3_tns_analyze (TNS filter analysis)
fields:
  0x18  uint32_t     word0  
  0x1c  uint32_t     word1  
  0x20  uint32_t     word2  
  0x24  uint32_t     word3  
  0x28  uint32_t     word4  

<ground-truth bundle for stack_1387>
### cluster stack_1387  (stack, 1 members, 5 fields, size>=0x2c)

Stack-frame local local_154 in lc3_tns_analyze (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: lc3; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - lc3_tns_analyze @ 0x6ffd8  as local_154  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1387 {
    uint8_t    _pad_0x0[0x18];   /* +0x0 pad */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=idx4 */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
};
```
