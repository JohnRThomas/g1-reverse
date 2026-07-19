## review group param_0499  (1 cluster(s), kinds=param)

### proposal for param_0499
struct_name: ldiv5_result | is_library: True | library_name: newlib internal (_ldiv5 helper, part of dtoa/vfprintf float formatting) | is_array: False | confidence: medium
purpose: Output parameter of newlib internal helper _ldiv5 (64-bit divide-by-5 used by floating-point printf), pointer to a 64-bit unsigned result written in place.
fields:
  0x0  uint64_t     result  64-bit quotient written by the helper

<ground-truth bundle for param_0499>
### cluster param_0499  (param, 1 members, 2 fields, size>=0xc)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (1 shown of 1):
  - _ldiv5 @ 0x7e260  as param_1  [APPLICATION]

layout notes: 0x0: access width 8 exceeds gap 4 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0499 {
    uint32_t   field_0x0;   /* +0x0  sz=8 rw=w types=ulonglong */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x8[0x4];   /* +0x8 pad */
};
```
