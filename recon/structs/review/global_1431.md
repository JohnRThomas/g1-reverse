## review group global_1431  (1 cluster(s), kinds=global)

### proposal for global_1431
struct_name: scanf_field_parse_ctx | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Global scratch context used by scanf_convert_integer_field to hold parse state (base/width or similar)
fields:
  0x4  uint32_t     field_0x4  read-only parse parameter
  0x8  uint32_t     field_0x8  read-only parse parameter

<ground-truth bundle for global_1431>
### cluster global_1431  (global, 1 members, 2 fields, size>=0xc)

Global object at fixed address 0x00079518.

library hint: likely G1-original

members (1 shown of 1):
  - scanf_convert_integer_field @ 0x7932c  as 0x00079518  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct global_1431 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
