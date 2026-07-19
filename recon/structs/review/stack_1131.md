## review group stack_1131  (1 cluster(s), kinds=stack)

### proposal for stack_1131
struct_name: storage_erase_range_tmp | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Stack-local erase range (address/size style pair) inside storage_erase_handler
fields:
  0x0  uint32_t     field_0x0  
  0x14  uint32_t     field_0x14  

<ground-truth bundle for stack_1131>
### cluster stack_1131  (stack, 1 members, 2 fields, size>=0x18)

Stack-frame local local_2c in storage_erase_handler (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - storage_erase_handler @ 0x52604  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1131 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x10];   /* +0x4 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```
