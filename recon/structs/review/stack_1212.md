## review group stack_1212  (1 cluster(s), kinds=stack)

### proposal for stack_1212
struct_name: att_find_type_req_locals | is_library: True | library_name: bt_att find-type-req locals | is_array: None | confidence: low
purpose: Zephyr BT ATT 'Find Type Value Request' local fragment inside att_find_type_req (attribute-type byte plus a second byte two positions later).
fields:
  0x0  uint8_t      field_0  read-only byte
  0x2  uint8_t      field_2  read-only byte

<ground-truth bundle for stack_1212>
### cluster stack_1212  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_38 in att_find_type_req (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: att; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - att_find_type_req @ 0x59550  as local_38  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1212 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
