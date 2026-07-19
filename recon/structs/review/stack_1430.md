## review group stack_1430  (1 cluster(s), kinds=stack)

### proposal for stack_1430
struct_name: scanf_int_convert_locals | is_library: False | library_name:  | is_array: None | confidence: low
purpose: Local scratch values used by scanf_convert_integer_field while parsing an integer field (accumulator, sign, width, result)
fields:
  0x0  uint32_t     local_val0  idx4
  0x4  uint32_t     local_val1  idx4
  0x8  uint32_t     local_val2  idx4
  0x10  uint32_t     local_val3  idx4

<ground-truth bundle for stack_1430>
### cluster stack_1430  (stack, 1 members, 4 fields, size>=0x14)

Stack-frame local local_34 in scanf_convert_integer_field (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - scanf_convert_integer_field @ 0x7932c  as local_34  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1430 {
    uint32_t   field_0x0;   /* +0x0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x4];   /* +0xc pad */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=idx4 */
};
```
