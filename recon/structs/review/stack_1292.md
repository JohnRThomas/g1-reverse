## review group stack_1292  (1 cluster(s), kinds=stack)

### proposal for stack_1292
struct_name: cjson_printbuffer_locals | is_library: True | library_name: printbuffer (cJSON) | is_array: None | confidence: low
purpose: cJSON internal printbuffer/format-state local used inside cjson_print_value while serializing a JSON value.
fields:
  0x0  uint16_t     format_flags  read-only ushort
  0x1c  uint16_t     trailing_field  read-only ushort near end

<ground-truth bundle for stack_1292>
### cluster stack_1292  (stack, 1 members, 2 fields, size>=0x1e)

Stack-frame local local_40 in cjson_print_value (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: cjson; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - cjson_print_value @ 0x646c0  as local_40  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1292 {
    uint16_t   field_0x0;   /* +0x0  sz=2 rw=r types=idx2 */
    uint8_t    _pad_0x2[0x1a];   /* +0x2 pad */
    uint16_t   field_0x1c;   /* +0x1c  sz=2 rw=r types=idx2 */
};
```
