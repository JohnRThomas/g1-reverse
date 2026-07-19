## review group stack_1016  (1 cluster(s), kinds=stack)

### proposal for stack_1016
struct_name: bitmap_merge_local | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Stack-local pair used in gui_bitmps_merge_draw, likely coordinate/size pair
fields:
  0x0  uint32_t     field_0x0  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for stack_1016>
### cluster stack_1016  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_2c in gui_bitmps_merge_draw (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - gui_bitmps_merge_draw @ 0x43bd8  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1016 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
