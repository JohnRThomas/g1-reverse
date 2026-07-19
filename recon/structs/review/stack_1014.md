## review group stack_1014  (1 cluster(s), kinds=stack)

### proposal for stack_1014
struct_name: bmp_draw_desc | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Stack-local bitmap draw descriptor in gui_bmp_dynamic_bitmap_draw: a leading word (pointer or dimension) and a second word 8 bytes later (size or second dimension).
fields:
  0x0  uint32_t     field_0x0  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for stack_1014>
### cluster stack_1014  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_24 in gui_bmp_dynamic_bitmap_draw (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - gui_bmp_dynamic_bitmap_draw @ 0x4334c  as local_24  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1014 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
