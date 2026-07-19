## review group param_0028  (1 cluster(s), kinds=param)

### proposal for param_0028
struct_name: gpio_pin_desc | is_library: True | library_name: gpio_dt_spec (approx) | is_array: None | confidence: low
purpose: GPIO pin/port descriptor consumed by gpio_pin_configure, carrying a config-flags byte and a pin/mask field.
fields:
  0x1  uint8_t      cfg_flags  single byte, read
  0x6  uint16_t     pin_mask  ushort, read

<ground-truth bundle for param_0028>
### cluster param_0028  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - gpio_pin_configure_17688 @ 0x17688  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0028 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte */
    uint8_t    _pad_0x2[0x4];   /* +0x2 pad */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=r types=ushort */
};
```
