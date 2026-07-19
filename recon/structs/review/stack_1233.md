## review group stack_1233  (1 cluster(s), kinds=stack)

### proposal for stack_1233
struct_name: gatt_handle_range | is_library: True | library_name: bt_gatt handle range (local, not a stock header type) | is_array: None | confidence: medium
purpose: Local pair of ATT handles parsed from a Find-By-Type-Value response entry in gatt_parse_find_by_type_rsp.
fields:
  0x0  uint32_t     start_handle  read as idx4
  0xc  uint32_t     end_handle  read as idx4

<ground-truth bundle for stack_1233>
### cluster stack_1233  (stack, 1 members, 2 fields, size>=0x10)

Stack-frame local local_3c in gatt_parse_find_by_type_rsp (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_parse_find_by_type_rsp @ 0x5bbf4  as local_3c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1233 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x8];   /* +0x4 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
