## review group param_0247  (1 cluster(s), kinds=param)

### proposal for param_0247
struct_name: sllist_node_refcounted | is_library: False | library_name:  | is_array: None | confidence: medium
purpose: G1-original singly/doubly linked-list node with a refcount/flags word and next pointer, used for GATT subscription-record release and generic list unlink
fields:
  0x8  int32_t      ref_count_or_flags  rw
  0xc  void*        next  rw

<ground-truth bundle for param_0247>
### cluster param_0247  (param, 2 members, 2 fields, size>=0x10)

Shared pointer-parameter object unified across call-argument flow.

library hint: LIKELY LIBRARY (prefixes: gatt; 0/2 members are LIBRARY-class)

members (2 shown of 2):
  - gatt_sub_free @ 0x59e78  as param_1  [APPLICATION]
  - list_unlink_and_release @ 0x828e8  as param_2  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0247 {
    uint8_t    _pad_0x0[0x8];   /* +0x0 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=rw types=int,undefined4 */
    void *     field_0xc;   /* +0xc  sz=4 rw=rw types=ptr,undefined4 */
};
```
