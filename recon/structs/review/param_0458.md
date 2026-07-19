## review group param_0458  (1 cluster(s), kinds=param)

### proposal for param_0458
struct_name: opt_node_header | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Small header struct read by opt_node_header_len holding two size/length words.
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for param_0458>
### cluster param_0458  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - opt_node_header_len @ 0x7c3ea  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0458 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
