## review group stack_1033  (1 cluster(s), kinds=stack)

### proposal for stack_1033
struct_name: gui_draw_point | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local coordinate pair used by gui_string_draw when positioning glyphs on screen.
fields:
  0x0  uint32_t     x  
  0x8  uint32_t     y  

<ground-truth bundle for stack_1033>
### cluster stack_1033  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_2c in gui_string_draw (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - gui_string_draw @ 0x455cc  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1033 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
