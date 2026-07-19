## review group stack_0942  (1 cluster(s), kinds=stack)

### proposal for stack_0942
struct_name: config_record_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local scratch in commit_default_config_record holding a record id byte and a trailing flag byte.
fields:
  0x0  uint8_t      record_id  read
  0x4  uint8_t      flag  read

<ground-truth bundle for stack_0942>
### cluster stack_0942  (stack, 1 members, 2 fields, size>=0x5)

Stack-frame local local_1c in commit_default_config_record (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - commit_default_config_record @ 0x30710  as local_1c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0942 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```
