## review group stack_1050  (1 cluster(s), kinds=stack)

### proposal for stack_1050
struct_name: display_close_locals | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Small local scratch in display_close, likely a 2-3 byte status/flag pair used while tearing down the display.
fields:
  0x0  uint8_t      field_0x0  
  0x2  uint8_t      field_0x2  

<ground-truth bundle for stack_1050>
### cluster stack_1050  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_28 in display_close (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - display_close @ 0x497b0  as local_28  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1050 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
