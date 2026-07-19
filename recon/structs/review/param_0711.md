## review group param_0711  (1 cluster(s), kinds=param)

### proposal for param_0711
struct_name: unk_ctx_0711 | is_library: False | library_name:  | is_array: False | confidence: low
purpose: G1-original context passed as param_2 to unnamed FUN_00085a04.
fields:
  0x20  uint32_t     field_0x20  
  0x24  uint32_t     field_0x24  

<ground-truth bundle for param_0711>
### cluster param_0711  (param, 1 members, 2 fields, size>=0x28)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_00085a04 @ 0x85a04  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0711 {
    uint8_t    _pad_0x0[0x20];   /* +0x0 pad */
    uint32_t   field_0x20;   /* +0x20  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x24;   /* +0x24  sz=4 rw=r types=int */
};
```
