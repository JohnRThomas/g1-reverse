### cluster stack_1219  (stack, 1 members, 2 fields, size>=0x8)

Stack-frame local local_2a in bt_gatt_foreach_attr_type (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_gatt_foreach_attr_type @ 0x5aa84  as local_2a  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1219 {
    uint16_t   field_0x0;   /* +0x0  sz=2 rw=r types=idx2 */
    uint8_t    _pad_0x2[0x4];   /* +0x2 pad */
    uint16_t   field_0x6;   /* +0x6  sz=2 rw=r types=idx2 */
};
```