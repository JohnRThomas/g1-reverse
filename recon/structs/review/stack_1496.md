## review group stack_1496  (1 cluster(s), kinds=stack)

### proposal for stack_1496
struct_name: projector_cmd_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local 6-byte command buffer built in projector_send_cmd_immediate before sending to the AR display projector.
fields:
  0x0  uint8_t      cmd_id  read
  0x5  uint8_t      param_or_checksum  read

<ground-truth bundle for stack_1496>
### cluster stack_1496  (stack, 1 members, 2 fields, size>=0x6)

Stack-frame local local_11 in projector_send_cmd_immediate (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - projector_send_cmd_immediate @ 0x7d77c  as local_11  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1496 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x4];   /* +0x1 pad */
    uint8_t    field_0x5;   /* +0x5  sz=1 rw=r types=idx1 */
};
```
