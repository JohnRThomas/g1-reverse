## review group stack_1018  (1 cluster(s), kinds=stack)

### proposal for stack_1018
struct_name: scroll_text_frame_ctx | is_library: False | library_name:  | is_array: True | confidence: low
purpose: Stack-local frame-rendering scratch (indices/offsets) inside ui_render_scroll_text_frame for computing scrolling text glyph layout.
fields:
  0x0  uint32_t     field_0x0  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  
  0x10  uint32_t     field_0x10  
  0x14  uint32_t     field_0x14  
  0x18  uint32_t     field_0x18  
  0x1c  uint32_t     field_0x1c  
  0x20  uint32_t     field_0x20  
  0x28  uint32_t     field_0x28  

<ground-truth bundle for stack_1018>
### cluster stack_1018  (stack, 1 members, 10 fields, size>=0x2c)

Stack-frame local local_4c in ui_render_scroll_text_frame (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - ui_render_scroll_text_frame @ 0x440ec  as local_4c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1018 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x18;   /* +0x18  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1c;   /* +0x1c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x24[0x4];   /* +0x24 pad */
    uint32_t   field_0x28;   /* +0x28  sz=4 rw=r types=idx4 */
};
```
