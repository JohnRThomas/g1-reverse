## review group stack_1427  (1 cluster(s), kinds=stack)

### proposal for stack_1427
struct_name: strtod_local | is_library: True | library_name: strtod_state | is_array: None | confidence: low
purpose: Local stack struct in strtod holding two 32-bit intermediate parsing values (mantissa/exponent)
fields:
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  

<ground-truth bundle for stack_1427>
### cluster stack_1427  (stack, 1 members, 2 fields, size>=0xc)

Stack-frame local local_3c in strtod (not shared across functions).

library hint: likely G1-original

members (1 shown of 1):
  - strtod @ 0x77a10  as local_3c  [APPLICATION]

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct stack_1427 {
    uint8_t    _pad_0x0[0x4];   /* +0x0 pad */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
};
```
