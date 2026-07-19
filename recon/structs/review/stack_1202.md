## review group stack_1202  (1 cluster(s), kinds=stack)

### proposal for stack_1202
struct_name: att_read_group_type_req | is_library: True | library_name: bt_att | is_array: None | confidence: low
purpose: Zephyr BLE ATT 'Read By Group Type Request' local PDU fields in att_read_group_req: type/format index and a second index byte
fields:
  0x0  uint8_t      field_0x0  read-only idx1
  0x2  uint8_t      field_0x2  read-only idx1

<ground-truth bundle for stack_1202>
### cluster stack_1202  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_44 in att_read_group_req (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: att; 1/1 members are LIBRARY-class)

members (1 shown of 1):
  - att_read_group_req @ 0x591a0  as local_44  [LIBRARY]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1202 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
