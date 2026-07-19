## review group param_0305  (1 cluster(s), kinds=param)

### proposal for param_0305
struct_name: unk_ctx_305 | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Small context object read by an unnamed function (FUN_00061ba0): a pointer field and an unrelated later integer field; insufficient evidence for precise semantics.
fields:
  0x4  void *       ptr_field  
  0x10  int32_t      int_field  

<ground-truth bundle for param_0305>
### cluster param_0305  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_00061ba0 @ 0x61ba0  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0305 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
