## review group stack_1036  (1 cluster(s), kinds=stack)

### proposal for stack_1036
struct_name: lcd_fb_xfer_local | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Stack-local pair of bytes used in reflash_fb_data_to_lcd during framebuffer-to-LCD transfer.
fields:
  0x0  uint8_t      field_0x0  status/index byte
  0x4  uint8_t      field_0x4  status/index byte

<ground-truth bundle for stack_1036>
### cluster stack_1036  (stack, 1 members, 2 fields, size>=0x5)

Stack-frame local local_38 in reflash_fb_data_to_lcd (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - reflash_fb_data_to_lcd @ 0x47260  as local_38  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1036 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```
