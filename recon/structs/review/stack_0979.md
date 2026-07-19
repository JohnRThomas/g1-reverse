## review group stack_0979  (1 cluster(s), kinds=stack)

### proposal for stack_0979
struct_name: float_screen_render_params | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local triple of render parameters (position or dimension values) in render_device_info_float_screen.
fields:
  0x0  float        param_x  read-only, likely x coordinate/width
  0x4  float        param_y  read-only, likely y coordinate/height
  0x8  float        param_z  read-only, likely depth/scale

<ground-truth bundle for stack_0979>
### cluster stack_0979  (stack, 1 members, 3 fields, size>=0xc)

Stack-frame local local_38 in render_device_info_float_screen (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - render_device_info_float_screen @ 0x361d8  as local_38  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0979 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
