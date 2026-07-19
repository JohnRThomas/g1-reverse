## review group stack_1079  (1 cluster(s), kinds=stack)

### proposal for stack_1079
struct_name: discovery_result_flags | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local pair of index bytes in discovery_callback describing a discovered BLE attribute (type + length/flags)
fields:
  0x0  uint8_t      type_idx  read-only idx1
  0x2  uint8_t      len_idx  read-only idx1

<ground-truth bundle for stack_1079>
### cluster stack_1079  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_38 in discovery_callback (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - discovery_callback @ 0x4ea78  as local_38  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1079 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
