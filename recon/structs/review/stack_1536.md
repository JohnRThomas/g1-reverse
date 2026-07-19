## review group stack_1536  (1 cluster(s), kinds=stack)

### proposal for stack_1536
struct_name: unk_stack_1536 | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Small stack-local scratch inside unnamed FUN_00082d6a.
fields:
  0x0  uint8_t      field_0x0  
  0x2  uint8_t      field_0x2  

<ground-truth bundle for stack_1536>
### cluster stack_1536  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_48 in FUN_00082d6a (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - FUN_00082d6a @ 0x82d6a  as local_48  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1536 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
