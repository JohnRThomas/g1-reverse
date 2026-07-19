## review group param_0505  (1 cluster(s), kinds=param)

### proposal for param_0505
struct_name: generic_handle_ctx | is_library: False | library_name:  | is_array: None | confidence: low
purpose: G1-original context object read by FUN_0007eb5c: a pointer field and a separate integer field.
fields:
  0x4  void *       field_0x4  read-only pointer
  0x10  int32_t      field_0x10  read-only int

<ground-truth bundle for param_0505>
### cluster param_0505  (param, 1 members, 2 fields, size>=0x14)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_0007eb5c @ 0x7eb5c  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0505 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    void *     field_0x4;   /* +0x4  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x8[0x8];   /* +0x8 pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
};
```
