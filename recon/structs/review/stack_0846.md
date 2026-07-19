## review group stack_0846  (1 cluster(s), kinds=stack)

### proposal for stack_0846
struct_name: debug_print_buf | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Local stack buffer in debug_print used to format a debug message string
fields:
  0x0  uint8_t      field_0x0  
  0xc8  uint8_t      field_0xc8  

<ground-truth bundle for stack_0846>
### cluster stack_0846  (stack, 1 members, 2 fields, size>=0xc9)

Stack-frame local local_e8 in debug_print (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - debug_print @ 0x19c70  as local_e8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0846 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0xc7];   /* +0x1 pad */
    uint8_t    field_0xc8;   /* +0xc8  sz=1 rw=r types=idx1 */
};
```
