## review group stack_1571  (1 cluster(s), kinds=stack)

### proposal for stack_1571
struct_name: dtoa_locals | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Local pair of integer values (e.g. exponent and digit count) used by dtoa_format_cvt during double-to-ASCII conversion.
fields:
  0x0  int32_t      exponent  first local int
  0x8  int32_t      digit_count  second local int

<ground-truth bundle for stack_1571>
### cluster stack_1571  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_2c in dtoa_format_cvt (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - dtoa_format_cvt @ 0x86cda  as local_2c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1571 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4[0x4];   /* +0x4 pad */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
