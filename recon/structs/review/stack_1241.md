## review group stack_1241  (1 cluster(s), kinds=stack)

### proposal for stack_1241
struct_name: find_info_rsp_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local (format,count) pair parsed from an ATT Find Information Response in gatt_parse_find_info_rsp
fields:
  0x0  uint8_t      fmt  r, idx1 — UUID16 vs UUID128 format byte
  0x2  uint8_t      count_or_len  r, idx1

<ground-truth bundle for stack_1241>
### cluster stack_1241  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_54 in gatt_parse_find_info_rsp (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_parse_find_info_rsp @ 0x5c0bc  as local_54  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1241 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
