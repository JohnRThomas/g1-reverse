## review group stack_0981  (1 cluster(s), kinds=stack)

### proposal for stack_0981
struct_name: timer_hms_draw_tmp | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local pair of 16-bit values used while drawing an h:m:s timer widget in gui_draw_timer_hms
fields:
  0x0  uint16_t     value_a  r, idx2
  0x6  uint16_t     value_b  r, idx2

<ground-truth bundle for stack_0981>
### cluster stack_0981  (stack, 1 members, 2 fields, size>=0x8)

Stack-frame local local_2a in gui_draw_timer_hms (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - gui_draw_timer_hms @ 0x362e8  as local_2a  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0981 {
    uint16_t   field_0x0;   /* +0x0  sz=2 rw=r types=idx2 */
    uint8_t    _pad_0x2[0x4];   /* +0x2 pad */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=r types=idx2 */
};
```
