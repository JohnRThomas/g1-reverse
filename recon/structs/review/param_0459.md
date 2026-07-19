## review group param_0459  (1 cluster(s), kinds=param)

### proposal for param_0459
struct_name: opt_node_t | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: Serializable option/attribute list node used throughout the opt_node_* serialization routines (opt_node_serialize, opt_list_append_node, etc.)
fields:
  0x1  uint8_t      type  r
  0x2  uint8_t      flags  r
  0x4  uint32_t     next  r, idx4 — likely list link
  0x8  uint32_t     child_or_value_ptr  r, idx4
  0xc  uint32_t     value_ptr  r
  0x10  uint32_t     value_len  r
  0x14  int32_t      extra  r
  0x60  uint32_t     sub_field_0  r, idx4
  0x64  uint32_t     sub_field_1  r, idx4
  0x68  uint32_t     sub_field_2  r, idx4
  0x6c  uint32_t     sub_field_3  r, idx4

<ground-truth bundle for param_0459>
### cluster param_0459  (param, 6 members, 11 fields, size>=0x70)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (6 shown of 6):
  - opt_node_value_len @ 0x7c408  as param_1  [APPLICATION]
  - opt_node_serialize_7c5ba @ 0x7c5ba  as param_1  [APPLICATION]
  - serialization_copy_fields_0c_10 @ 0x7c65c  as param_1  [APPLICATION]
  - serialization_read_or_copy @ 0x7c670  as param_1  [APPLICATION]
  - opt_node_serialize @ 0x7c6a0  as param_1  [APPLICATION]
  - opt_list_append_node @ 0x7c7de  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0459 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=r types=byte,char */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0x3[0x1];   /* +0x3 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4,undefined4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4,undefined4 */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=undefined4 */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=int */
    uint8_t    _pad_0x18[0x48];   /* +0x18 pad */
    uint32_t   field_0x60;   /* +0x60  sz=4 rw=r types=idx4 */
    uint32_t   field_0x64;   /* +0x64  sz=4 rw=r types=idx4 */
    uint32_t   field_0x68;   /* +0x68  sz=4 rw=r types=idx4 */
    uint32_t   field_0x6c;   /* +0x6c  sz=4 rw=r types=idx4 */
};
```
