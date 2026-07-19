## review group stack_0790  (1 cluster(s), kinds=stack)

### proposal for stack_0790
struct_name: hci_vs_init_locals | is_library: True | library_name:  | is_array: None | confidence: low
purpose: Local Zephyr HCI vendor-specific init temporaries (two words used to build a Bluetooth HCI command)
fields:
  0x0  uint32_t     field_0x0  
  0x10  uint32_t     field_0x10  

<ground-truth bundle for stack_0790>
### cluster stack_0790  (stack, 1 members, 2 fields, size>=0x14)

Stack-frame local local_30 in hci_vs_init (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: hci; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - hci_vs_init @ 0x12080  as local_30  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0790 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0xc];   /* +0x4 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
