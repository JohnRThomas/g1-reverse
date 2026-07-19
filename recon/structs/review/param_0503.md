## review group param_0503  (1 cluster(s), kinds=param)

### proposal for param_0503
struct_name: generic_uint32_pair | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Small unnamed two-field object (offsets 0x4/0x8) used only within FUN_0007e6a6; insufficient naming signal.
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for param_0503>
### cluster param_0503  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_0007e6a6 @ 0x7e6a6  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0503 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
