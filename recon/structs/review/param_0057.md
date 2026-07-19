## review group param_0057  (1 cluster(s), kinds=param)

### proposal for param_0057
struct_name: box_event | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Event/message struct passed to process_box_event describing a UI 'box' event (type + payload word).
fields:
  0x2  uint8_t      event_type  event type/subtype byte, read-write
  0x8  uint32_t     payload  event payload/value, read-only in this function

<ground-truth bundle for param_0057>
### cluster param_0057  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - process_box_event @ 0x254d8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0057 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0x3[0x5];   /* +0x3 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint,undefined4 */
};
```
