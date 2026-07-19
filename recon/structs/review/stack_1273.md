## review group stack_1273  (1 cluster(s), kinds=stack)

### proposal for stack_1273
struct_name: pdm_mic_event_data | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local PDM microphone event data in pdm_mic_event_handler: a buffer pointer/index and a status/size index at a later offset
fields:
  0x0  uint32_t     field_0x0  read-only idx4, likely buffer pointer/index
  0x10  uint32_t     field_0x10  read-only idx4, likely size/status

<ground-truth bundle for stack_1273>
### cluster stack_1273  (stack, 1 members, 2 fields, size>=0x14)

Stack-frame local local_30 in pdm_mic_event_handler (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - pdm_mic_event_handler @ 0x5ffa4  as local_30  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1273 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0xc];   /* +0x4 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
