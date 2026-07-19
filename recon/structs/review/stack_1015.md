## review group stack_1015  (1 cluster(s), kinds=stack)

### proposal for stack_1015
struct_name: gui_bitmap_draw_args | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local pair of index fields in gui_bitmap_draw, likely bitmap width/stride and height or an x/y offset pair
fields:
  0x0  uint32_t     field_0x0  read-only idx4
  0x8  uint32_t     field_0x8  read-only idx4

<ground-truth bundle for stack_1015>
### cluster stack_1015  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_2c in gui_bitmap_draw (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - gui_bitmap_draw @ 0x43a68  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1015 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
