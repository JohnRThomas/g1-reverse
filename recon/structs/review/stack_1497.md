## review group stack_1497  (1 cluster(s), kinds=stack)

### proposal for stack_1497
struct_name: proj_cmd_locals | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Local command/parameter byte pair built by projector_send_cmd_immediate before sending to the projector.
fields:
  0x0  uint8_t      cmd_byte  command opcode byte
  0x4  uint8_t      param_byte  command parameter byte

<ground-truth bundle for stack_1497>
### cluster stack_1497  (stack, 1 members, 2 fields, size>=0x5)

Stack-frame local local_c in projector_send_cmd_immediate (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - projector_send_cmd_immediate @ 0x7d77c  as local_c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1497 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```
