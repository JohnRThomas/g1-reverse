## review group global_1323  (1 cluster(s), kinds=global)

### proposal for global_1323
struct_name: pdm_pin_state_table | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Large global buffer/table for PDM microphone pin configuration; only two trailer fields written by pdm_configure_pins
fields:
  0x520  uint32_t     pin_config_flags  written by pdm_configure_pins
  0x540  uint32_t     pin_config_status  written by pdm_configure_pins, trailer field after 0x1c pad

<ground-truth bundle for global_1323>
### cluster global_1323  (global, 1 members, 2 fields, size>=0x544)

Global object at fixed address 0x0006612c.

library hint: likely G1-original

members (1 shown of 1):
  - pdm_configure_pins @ 0x66050  as 0x0006612c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1323 {
    uint8_t    _pad_0x0[0x520];   /* +0x0 pad */
    uint32_t   field_0x520;   /* +0x520  sz=4 rw=w types=uint */
    uint8_t    _pad_0x524[0x1c];   /* +0x524 pad */
    uint32_t   field_0x540;   /* +0x540  sz=4 rw=w types=undefined4 */
};
```
