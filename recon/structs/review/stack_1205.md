## review group stack_1205  (1 cluster(s), kinds=stack)

### proposal for stack_1205
struct_name: local_pair_5929c | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Stack-local pair of index words in FUN_0005929c
fields:
  0x0  uint32_t     field_0x0  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for stack_1205>
### cluster stack_1205  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_30 in FUN_0005929c (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - FUN_0005929c @ 0x5929c  as local_30  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1205 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
