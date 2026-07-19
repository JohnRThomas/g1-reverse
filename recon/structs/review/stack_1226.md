## review group stack_1226  (1 cluster(s), kinds=stack)

### proposal for stack_1226
struct_name: gatt_notify_cb_local | is_library: True | library_name: bt_gatt_notify_cb (local) | is_array: None | confidence: low
purpose: Stack-local pair of bytes in Zephyr's bt_gatt_notify_cb, likely an error code and a state byte.
fields:
  0x0  uint8_t      field_0x0  result/error byte
  0x2  uint8_t      field_0x2  state/flags byte

<ground-truth bundle for stack_1226>
### cluster stack_1226  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_28 in bt_gatt_notify_cb (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_gatt_notify_cb @ 0x5b754  as local_28  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1226 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
