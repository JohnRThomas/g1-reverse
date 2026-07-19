## review group stack_1237  (1 cluster(s), kinds=stack)

### proposal for stack_1237
struct_name: gatt_read_by_type_rsp_cursor | is_library: True | library_name: Zephyr Bluetooth GATT (ATT Read By Type response parsing locals) | is_array: None | confidence: low
purpose: Local parse cursor in gatt_parse_read_by_type_rsp_128 tracking a type-length byte and a following byte, separated by one pad byte.
fields:
  0x0  uint8_t      field_0x0  read-only byte, idx1
  0x2  uint8_t      field_0x2  read-only byte, idx1

<ground-truth bundle for stack_1237>
### cluster stack_1237  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_4c in gatt_parse_read_by_type_rsp_128 (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_parse_read_by_type_rsp_128 @ 0x5c004  as local_4c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1237 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
