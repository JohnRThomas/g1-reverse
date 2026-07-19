## review group param_0189  (1 cluster(s), kinds=param)

### proposal for param_0189
struct_name: bt_hci_cmd_state_set | is_library: True | library_name: struct bt_hci_cmd_state_set | is_array: None | confidence: low
purpose: Zephyr BT HCI command-state descriptor: target atomic flag pointer/bit and a boolean value, set up by bt_hci_cmd_state_set_init.
fields:
  0x2  uint8_t      field_0x2  
  0x4  uint32_t     bit_or_val  

<ground-truth bundle for param_0189>
### cluster param_0189  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: bt; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - bt_hci_cmd_state_set_init @ 0x53cb0  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0189 {
    uint8_t    _pad_0x0[0x2];   /* +0x0 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
