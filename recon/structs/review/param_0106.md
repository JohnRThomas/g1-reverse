## review group param_0106  (1 cluster(s), kinds=param)

### proposal for param_0106
struct_name: draw_message_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Message-draw context passed to draw_message: a type/kind byte and a separate flag/format byte
fields:
  0x14  uint8_t      msg_type  read-only char
  0x1c  uint8_t      msg_flags  read-only char

<ground-truth bundle for param_0106>
### cluster param_0106  (param, 1 members, 2 fields, size>=0x1d)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - draw_message @ 0x35afc  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0106 {
    uint8_t    _pad_0x0[0x14];   /* +0x0 pad */
    uint8_t    field_0x14;   /* +0x14  sz=1 rw=r types=char */
    uint8_t    _pad_0x15[0x7];   /* +0x15 pad */
    uint8_t    field_0x1c;   /* +0x1c  sz=1 rw=r types=char */
};
```
