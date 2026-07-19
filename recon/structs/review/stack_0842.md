## review group stack_0842  (1 cluster(s), kinds=stack)

### proposal for stack_0842
struct_name: ancs_notify_buf | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Local stack buffer in ancs_notification_forward holding an Apple Notification Center Service (ANCS) message payload with a leading tag byte and trailing terminator byte
fields:
  0x0  uint8_t      msg_tag  
  0x180  uint8_t      msg_terminator  

<ground-truth bundle for stack_0842>
### cluster stack_0842  (stack, 1 members, 2 fields, size>=0x181)

Stack-frame local local_1b4 in ancs_notification_forward (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - ancs_notification_forward @ 0x1965c  as local_1b4  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0842 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x17f];   /* +0x1 pad */
    uint8_t    field_0x180;   /* +0x180  sz=1 rw=r types=idx1 */
};
```
