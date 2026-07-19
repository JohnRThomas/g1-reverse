## review group stack_1234  (1 cluster(s), kinds=stack)

### proposal for stack_1234
struct_name: gatt_read_by_type_locals | is_library: True | library_name: bt_gatt read-by-type response parsing | is_array: False | confidence: low
purpose: Small local state (length/type byte) used while parsing a GATT Read-By-Type response in gatt_parse_read_by_type_rsp.
fields:
  0x0  uint8_t      elem_len  per-attribute length byte
  0x2  uint8_t      elem_flag  secondary byte, e.g. count/type

<ground-truth bundle for stack_1234>
### cluster stack_1234  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_5c in gatt_parse_read_by_type_rsp (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_parse_read_by_type_rsp @ 0x5bd18  as local_5c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1234 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
