## review group global_1026  (1 cluster(s), kinds=global)

### proposal for global_1026
struct_name: gui_wordwrap_state | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Global cursor/measurement state used by the GUI UTF-8 word-wrap text drawing routine
fields:
  0x2  uint16_t     field_0x2  possibly glyph/char count or pixel width accumulator
  0x4  uint32_t     field_0x4  idx4-typed; possibly a buffer index or pointer-like handle

<ground-truth bundle for global_1026>
### cluster global_1026  (global, 1 members, 2 fields, size>=0x8)

Global object at fixed address 0x000454a8.

library hint: likely G1-original

members (1 shown of 1):
  - gui_utf_Wordwrap_draw @ 0x451e0  as 0x000454a8  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1026 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint16_t   field_0x2;   /* +0x2  sz=2 rw=r types=undefined2 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
