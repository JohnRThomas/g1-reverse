## review group stack_1351  (1 cluster(s), kinds=stack)

### proposal for stack_1351
struct_name: nrfx_twim_irq_local | is_library: True | library_name: nrfx_twim (irq local) | is_array: None | confidence: low
purpose: Stack-local pair of bytes used inside nrfx_twim_irq_handler while servicing a TWIM interrupt.
fields:
  0x0  uint8_t      field_0x0  event/status byte
  0x4  uint8_t      field_0x4  event/status byte

<ground-truth bundle for stack_1351>
### cluster stack_1351  (stack, 1 members, 2 fields, size>=0x5)

Stack-frame local local_28 in nrfx_twim_irq_handler (not shared across functions).

library hint: LIKELY LIBRARY (prefixes: nrfx; 0/1 members are LIBRARY-class)

members (1 shown of 1):
  - nrfx_twim_irq_handler @ 0x67600  as local_28  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1351 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```
