## review group stack_1425  (1 cluster(s), kinds=stack)

### proposal for stack_1425
struct_name: strtod_bigint_scratch | is_library: True | library_name: Bigint / dtoa internal scratch (newlib) | is_array: None | confidence: low
purpose: Stack-local scratch state used by the standard-library strtod() implementation for big-integer/decimal conversion.
fields:
  0xc  int32_t      field_0xc  exponent or digit-count accumulator, read-write
  0x10  int32_t      field_0x10  scratch value
  0x14  int32_t      field_0x14  scratch value

<ground-truth bundle for stack_1425>
### cluster stack_1425  (stack, 1 members, 3 fields, size>=0x18)

Stack-frame local local_7c in strtod (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - strtod @ 0x77a10  as local_7c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1425 {
    uint8_t    _pad_0x0[0xc];   /* +0x0 pad */
    uint32_t   field_0xc;   /* +0xc  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0x10;   /* +0x10  sz=4 rw=r types=int */
    uint32_t   field_0x14;   /* +0x14  sz=4 rw=r types=int */
};
```
