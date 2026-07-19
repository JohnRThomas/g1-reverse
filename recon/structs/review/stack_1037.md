## review group stack_1037  (1 cluster(s), kinds=stack)

### proposal for stack_1037
struct_name: lcd_reflash_local_state | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Local status pair in reflash_fb_data_to_lcd_ex tracking framebuffer-to-LCD reflash progress
fields:
  0x0  uint8_t      reflash_status  
  0x4  uint8_t      reflash_flag  

<ground-truth bundle for stack_1037>
### cluster stack_1037  (stack, 1 members, 2 fields, size>=0x5)

Stack-frame local local_38 in reflash_fb_data_to_lcd_ex (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - reflash_fb_data_to_lcd_ex @ 0x473c8  as local_38  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1037 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```
