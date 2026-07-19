## review group stack_0776  (1 cluster(s), kinds=stack)

### proposal for stack_0776
struct_name: soc_curve_point | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local stack pair (soc index, voltage/value) used while building the battery SOC curve model table.
fields:
  0x0  uint32_t     soc_idx  
  0xc  uint32_t     value  

<ground-truth bundle for stack_0776>
### cluster stack_0776  (stack, 1 members, 2 fields, size>=0x10)

Stack-frame local local_48 in battery_soc_curve_model_init (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - battery_soc_curve_model_init @ 0xe53c  as local_48  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_0776 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x8];   /* +0x4 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=idx4 */
};
```
