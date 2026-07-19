## review group stack_1535  (1 cluster(s), kinds=stack)

### proposal for stack_1535
struct_name: local_pair_82c48 | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Stack-local pair of index words used in FUN_00082c48
fields:
  0x0  uint32_t     field_0x0  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for stack_1535>
### cluster stack_1535  (stack, 1 members, 2 fields, size>=0x14)

Stack-frame local local_21 in FUN_00082c48 (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - FUN_00082c48 @ 0x82c48  as local_21  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1535 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0xc];   /* +0x4 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
