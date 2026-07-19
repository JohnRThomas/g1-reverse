## review group stack_1136  (1 cluster(s), kinds=stack)

### proposal for stack_1136
struct_name: gatt_register_service_locals | is_library: True | library_name: bt_gatt_service | is_array: None | confidence: low
purpose: Small local flag pair in gatt_register_service (Zephyr GATT service registration path)
fields:
  0x0  uint8_t      flag_a  idx1
  0x2  uint8_t      flag_b  idx1

<ground-truth bundle for stack_1136>
### cluster stack_1136  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_44 in gatt_register_service_200028b8 (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: gatt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - gatt_register_service_200028b8 @ 0x52b48  as local_44  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1136 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
