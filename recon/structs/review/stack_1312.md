## review group stack_1312  (1 cluster(s), kinds=stack)

### proposal for stack_1312
struct_name: gpiote_evt_info | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local GPIOTE event info in gpiote_irq_handler: pin/event pair plus a third word (e.g. polarity or timestamp) read while dispatching the interrupt.
fields:
  0x0  uint32_t     pin  
  0x4  uint32_t     event_or_action  
  0xc  uint32_t     field_0xc  

<ground-truth bundle for stack_1312>
### cluster stack_1312  (stack, 1 members, 3 fields, size>=0x10)

Stack-frame local local_30 in gpiote_irq_handler (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - gpiote_irq_handler @ 0x65b9c  as local_30  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1312 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x4];   /* +0x8 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
