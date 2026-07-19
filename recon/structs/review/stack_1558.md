## review group stack_1558  (1 cluster(s), kinds=stack)

### proposal for stack_1558
struct_name: post_event_tag5_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local event-tag buffer in post_event_tag5 with a header byte and trailer byte across a 0x15-byte scratch area
fields:
  0x0  uint8_t      header_byte  idx1
  0x14  uint8_t      trailer_byte  idx1

<ground-truth bundle for stack_1558>
### cluster stack_1558  (stack, 1 members, 2 fields, size>=0x15)

Stack-frame local local_1c in post_event_tag5 (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - post_event_tag5 @ 0x848b0  as local_1c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1558 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x13];   /* +0x1 pad */
    uint8_t    field_0x14;   /* +0x14  sz=1 rw=r types=idx1 */
};
```
