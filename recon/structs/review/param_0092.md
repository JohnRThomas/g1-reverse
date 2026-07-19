## review group param_0092  (1 cluster(s), kinds=param)

### proposal for param_0092
struct_name: display_brightness_cmd | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Command struct read by set_display_brightness giving a brightness level and an associated flag/mode byte.
fields:
  0x4  uint8_t      brightness  read-only byte
  0x5  uint8_t      auto_mode  read-only byte, possibly auto-brightness flag

<ground-truth bundle for param_0092>
### cluster param_0092  (param, 1 members, 2 fields, size>=0x6)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - set_display_brightness @ 0x32254  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0092 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=byte */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=r types=byte */
};
```
