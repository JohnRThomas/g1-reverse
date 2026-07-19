## review group param_0698  (1 cluster(s), kinds=param)

### proposal for param_0698
struct_name: task_ctx_generic | is_library: False | library_name:  | is_array: None | confidence: low
purpose: G1-original context/config object read by FUN_000855e6: four consecutive words followed by a pointer after padding.
fields:
  0x4  int32_t      field_0x4  read-only int
  0x8  uint32_t     field_0x8  read-only uint
  0xc  uint32_t     field_0xc  read-only uint
  0x10  uint32_t     field_0x10  read-only uint
  0x30  void *       field_0x30  read-only pointer

<ground-truth bundle for param_0698>
### cluster param_0698  (param, 1 members, 5 fields, size>=0x34)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - FUN_000855e6 @ 0x855e6  as param_1  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0698 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=int */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=uint */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=r types=uint */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=uint */
    uint8_t    _pad_0x14[0x1c];   /* +0x14 pad */
    void *     field_0x30;   /* +0x30  sz=4 rw=r types=ptr */
};
```
