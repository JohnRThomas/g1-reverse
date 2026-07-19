## review group param_0460  (1 cluster(s), kinds=param)

### proposal for param_0460
struct_name: opt_field1_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Small option/TLV setter context for a boolean-like flag and an index, used by opt_field1_set.
fields:
  0x1  uint8_t      flag  
  0x4  uint32_t     idx  

<ground-truth bundle for param_0460>
### cluster param_0460  (param, 1 members, 2 fields, size>=0x8)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - opt_field1_set @ 0x7c430  as param_3  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0460 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte */
    uint8_t    _pad_0x2[0x2];   /* +0x2 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
};
```
