## review group stack_1195  (1 cluster(s), kinds=stack)

### proposal for stack_1195
struct_name: ad_type_match_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local (type,flag) pair used inside find_type_cb while scanning BLE advertising-data entries
fields:
  0x0  uint8_t      ad_type  r, idx1
  0x2  uint8_t      match_flag  r, idx1

<ground-truth bundle for stack_1195>
### cluster stack_1195  (stack, 1 members, 2 fields, size>=0x3)

Stack-frame local local_3c in find_type_cb (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - find_type_cb @ 0x583d0  as local_3c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1195 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x1];   /* +0x1 pad */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=idx1 */
};
```
