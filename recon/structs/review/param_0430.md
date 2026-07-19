## review group param_0430  (1 cluster(s), kinds=param)

### proposal for param_0430
struct_name: fmt_conv_spec | is_library: True | library_name: newlib/picolibc internal __sPRINTF/conv spec (best guess) | is_array: None | confidence: low
purpose: Internal printf/scanf format-conversion-specifier fragment shared by vfprintf_core, vfprintf_field_scan_match, and scanf_convert_integer_field: a width/precision-related 16-bit field.
fields:
  0x3  uint16_t     width_or_flags  

<ground-truth bundle for param_0430>
### cluster param_0430  (param, 3 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (3 shown of 3):
  - vfprintf_core @ 0x78f88  as param_2  [APPLICATION]
  - vfprintf_field_scan_match @ 0x79278  as param_3  [APPLICATION]
  - scanf_convert_integer_field @ 0x7932c  as param_3  [APPLICATION]

layout notes: 0x3: access width 2 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0430 {
    uint8_t    _pad_0x0[0x3];   /* +0x0 pad */
    uint8_t    field_0x3;   /* +0x3  sz=2 rw=r types=ushort */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
