## review group param_0466  (1 cluster(s), kinds=param)

### proposal for param_0466
struct_name: opt_record | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Option record value-binding structure used by opt_record_bind_value
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0xc  uint32_t     field_0xc  

<ground-truth bundle for param_0466>
### cluster param_0466  (param, 1 members, 3 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - opt_record_bind_value @ 0x7c61e  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0466 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=int */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=int */
};
```
