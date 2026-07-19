## review group stack_1081  (1 cluster(s), kinds=stack)

### proposal for stack_1081
struct_name: ancs_handle_scratch | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Small stack-local scratch (two index bytes) inside ancs_gatt_dm_assign_handles for ANCS GATT discovery-manager handle assignment.
fields:
  0x0  uint8_t      field_0x0  
  0x2  uint8_t      field_0x2  

<ground-truth bundle for stack_1081>
### cluster stack_1081  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_9c in ancs_gatt_dm_assign_handles (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - ancs_gatt_dm_assign_handles @ 0x4ee68  as local_9c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1081 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
