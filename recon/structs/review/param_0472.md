## review group param_0472  (1 cluster(s), kinds=param)

### proposal for param_0472
struct_name: opt_list_node | is_library: False | library_name:  | is_array: False | confidence: medium
purpose: G1-original singly-linked list node appended by opt_list_append_node.
fields:
  0x4  uint32_t     next  likely next-node link
  0x8  uint32_t     data  payload/value field

<ground-truth bundle for param_0472>
### cluster param_0472  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - opt_list_append_node @ 0x7c7de  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0472 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
