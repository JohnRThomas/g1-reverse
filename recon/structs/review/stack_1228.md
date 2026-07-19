## review group stack_1228  (1 cluster(s), kinds=stack)

### proposal for stack_1228
struct_name: gatt_discover_local | is_library: True | library_name: bt_gatt_discover (internal local) | is_array: False | confidence: low
purpose: Local scratch pair in bt_gatt_discover used while iterating ATT discovery responses (e.g. attribute type/uuid length byte)
fields:
  0x0  uint8_t      attr_type_or_flag  
  0x2  uint8_t      attr_len_or_flag  

<ground-truth bundle for stack_1228>
### cluster stack_1228  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_28 in bt_gatt_discover (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_gatt_discover @ 0x5b9cc  as local_28  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1228 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
