## review group stack_1240  (1 cluster(s), kinds=stack)

### proposal for stack_1240
struct_name: gatt_find_info_elem | is_library: True | library_name: ATT find-info-rsp element (BT host internal) | is_array: False | confidence: low
purpose: Local ATT Find-Information-Response element in gatt_parse_find_info_rsp: a leading handle/format byte and a following type byte.
fields:
  0x0  uint8_t      field_0x0  
  0x2  uint8_t      field_0x2  

<ground-truth bundle for stack_1240>
### cluster stack_1240  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_58 in gatt_parse_find_info_rsp (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_parse_find_info_rsp @ 0x5c0bc  as local_58  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1240 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
