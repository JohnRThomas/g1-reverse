### cluster stack_1173  (stack, 1 members, 2 fields, size>=0x18)

Stack-frame local local_34 in hci_read_static_addresses (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: hci; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - hci_read_static_addresses @ 0x55350  as local_34  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1173 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x10];   /* +0x4 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```