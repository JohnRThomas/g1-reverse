## review group stack_1278  (1 cluster(s), kinds=stack)

### proposal for stack_1278
struct_name: uarte_isr_scratch | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Stack-local scratch bytes inside uarte_nrfx_isr for holding status/error flags during interrupt handling.
fields:
  0x0  uint8_t      field_0x0  
  0x4  uint8_t      field_0x4  

<ground-truth bundle for stack_1278>
### cluster stack_1278  (stack, 1 members, 2 fields, size>=0x5)

Stack-frame local local_2c in uarte_nrfx_isr (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - uarte_nrfx_isr @ 0x6312c  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1278 {
    uint8_t    field_0x0;   /* +0x0  sz=1 rw=r types=idx1 */
    uint8_t    _pad_0x1[0x3];   /* +0x1 pad */
    uint8_t    field_0x4;   /* +0x4  sz=1 rw=r types=idx1 */
};
```
