## review group stack_1170  (1 cluster(s), kinds=stack)

### proposal for stack_1170
struct_name: ble_rpa_gen_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local scratch in ble_privacy_request_random_address, likely holding intermediate state for resolvable-private-address generation (leading state word plus trailing result word).
fields:
  0x0  uint32_t     state_word  read as idx4
  0x14  uint32_t     result_word  read as idx4

<ground-truth bundle for stack_1170>
### cluster stack_1170  (stack, 1 members, 2 fields, size>=0x18)

Stack-frame local local_34 in ble_privacy_request_random_address (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - ble_privacy_request_random_address @ 0x552ac  as local_34  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1170 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x10];   /* +0x4 pad */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=idx4 */
};
```
