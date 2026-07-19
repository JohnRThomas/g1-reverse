## review group param_0649  (1 cluster(s), kinds=param)

### proposal for param_0649
struct_name: generic_range_pair | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Simple start/end style pair (offsets 0x4 and 0x10) used within FUN_000837e8; low naming signal.
fields:
  0x4  int32_t      start  
  0x10  int32_t      end  

<ground-truth bundle for param_0649>
### cluster param_0649  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_000837e8 @ 0x837e8  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0649 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
